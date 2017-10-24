
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
  uint32_t num_elements = TABLE_BLOCK_SIZE*10;
  for(uint32_t i = 0; i < num_elements; ++i) {
    Component component{i,static_cast<double>(i)};
    table->insert_element(i,&component);
  }

  ASSERT_EQ(table->size(), num_elements);

  Table::Iterator* iterator = table->iterator();
  uint32_t i = 0;
  while (iterator->has_next()) {
    TBlock* block = iterator->next();
    ASSERT_EQ(block->m_size, 512);
    for (uint32_t j = 0; j < TABLE_BLOCK_SIZE && j < block->m_size; ++j, ++i) {
        Component* component = static_cast<Component*>(get_element(block, i));
        if(component != nullptr) {
          ASSERT_EQ(component->field1_, i);
          ASSERT_EQ(component->field2_, static_cast<double>(i));
        }
    }
  }
  delete iterator;
  ASSERT_EQ(i, num_elements);

  table->clear();
  ASSERT_EQ(table->size(),0);

  //std::set<uint32_t> data;

  //for(uint32_t i = 0; i < 10000; ++i) {
  //  table.insert(i,i,i);
  //  data.insert(i);
  //}

  //ASSERT_EQ(table.size(),10000);

  //for(uint32_t i = 0; i < 5000; ++i) {
  //  table.drop_row_by_id(i);
  //  data.erase(i);
  //}
  //ASSERT_EQ(table.size(),5000);

  //for(auto iter = table.begin(); iter != table.end(); ++iter) {
  //  data.erase(iter->m_id);
  //}

  //ASSERT_EQ(data.size(), 0);
  //ASSERT_EQ(table.size(), 5000);

  //BaseRow* row = table.get_row_by_id(7500);
  //ASSERT_EQ(row->m_id, 7500);
  
  delete table;
}
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}

