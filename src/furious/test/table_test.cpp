
#include "../data/table.h"

#include <gtest/gtest.h>
#include <set>

namespace furious {

struct Component {
  uint32_t field1_;
  double field2_;

  Component(uint32_t field1, double field2) : field1_(field1), field2_(field2) {}

  static std::string name() {
    return "Component";
  }

};

TEST(TableTest,TableWorks) {

  Table* table = new Table(Component::name(), sizeof(Component));
  uint32_t num_elements = TABLE_BLOCK_SIZE*2048;
  for(uint32_t i = 0; i < num_elements; ++i) {
    Component component{i,static_cast<double>(i)};
    table->insert_element(i,&component);
  }

  ASSERT_EQ(table->size(), num_elements);

  Table::Iterator* iterator = table->iterator();
  uint32_t counter = 0;
  uint32_t i = 0;
  while (iterator->has_next()) {
    TBlock* block = iterator->next();
    for (uint32_t j = 0; j < TABLE_BLOCK_SIZE; ++j, ++i) {
        Component* component = static_cast<Component*>(get_element(block, i));
        if(component != nullptr) {
          counter++;
          ASSERT_EQ(component->field1_, i);
          ASSERT_EQ(component->field2_, static_cast<double>(i));
        }
    }
  }
  delete iterator;
  ASSERT_EQ(counter, num_elements);
  ASSERT_EQ(table->size(), num_elements);

  for(uint32_t i = 0; i < num_elements; i+=2) {
    table->drop_element(i);
  }
  ASSERT_EQ(table->size(), num_elements/2);

  iterator = table->iterator();
  counter = 0;
  i = 0;
  while (iterator->has_next()) {
    TBlock* block = iterator->next();
    ASSERT_EQ(block->m_num_elements, TABLE_BLOCK_SIZE/2);
    for (uint32_t j = 0; j < TABLE_BLOCK_SIZE; ++j, ++i) {
        Component* component = static_cast<Component*>(get_element(block, i));
        if(component != nullptr) {
          counter++;
          ASSERT_EQ(component->field1_, i);
          ASSERT_EQ(component->field2_, static_cast<double>(i));
        }
    }
  }
  delete iterator;
  ASSERT_EQ(counter, num_elements/2);

  table->clear();
  ASSERT_EQ(table->size(),0);

  delete table;
}
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}

