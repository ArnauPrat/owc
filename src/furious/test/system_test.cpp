
#include "../runtime/static_system.h"
#include "data_test.h"

#include <gtest/gtest.h>

namespace furious {

class SystemTest : public DataTest {
};


class TestSystem {
public:
  TestSystem(uint32_t val) : m_val{val} {}
  virtual ~TestSystem() = default;

  void run(ComponentA* component) {
    component->field1_ *= m_val;
    component->field2_ *= m_val;
  }

  uint32_t m_val;
};

TEST_F(SystemTest, SystemWorks) {

  uint32_t num_elements = TABLE_BLOCK_SIZE * 10;
  for(uint32_t i = 0; i < num_elements; ++i) {
    ComponentA component{i*2,i*1.0};
    tableA_->insert_element(i,&component);
  }


  auto test_system = create_static_system<TestSystem>(5);

  Table::Iterator* it = tableA_->iterator();
  while(it->has_next()) {
    TBlock* next_block = it->next();
    std::vector<void*> blocks{next_block->p_data};
    test_system->apply_block(blocks);
  }
  delete it;

  uint32_t counter = 0;
  it = tableA_->iterator();
  while(it->has_next()) {
    TBlock* next_block = it->next();
    ComponentA* data = reinterpret_cast<ComponentA*>(next_block->p_data);
    for(uint32_t i = 0; i < TABLE_BLOCK_SIZE; ++i, ++counter) {
      ComponentA* component = &data[i];
      ASSERT_EQ(component->field1_, 5*counter*2);
      ASSERT_EQ(component->field2_, 5*counter*1.0);
    }
  }
  delete it;
  tableA_->clear();
}

} /* furious */ 

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
