
#include <gtest/gtest.h>
#include <data/static_system.h>
#include "data_test.h"

namespace furious {
namespace data {

class SystemTest : public DataTest {
};

class TestSystem : public StaticSystem<ComponentA> {
public:
  TestSystem(SystemId id) : StaticSystem(id) {}
  virtual ~TestSystem() = default;

  void run(ComponentA& component) override {
    component.field1_ = 0;
    component.field2_ = 0.0;
  }
};

TEST_F(SystemTest, SystemWorks) {

  for(uint32_t i = 0; i < 10000; ++i) {
    tableA_->insert(i,i*2,i*1.0);
  }

  TestSystem test_system(0);

  for(auto it = tableA_->begin(); it != tableA_->end(); ++it) {
    test_system.run(*static_cast<ComponentA*>(it->column(0)));
    ASSERT_EQ(static_cast<ComponentA*>(it->column(0))->field1_, 0);
    ASSERT_EQ(static_cast<ComponentA*>(it->column(0))->field2_, 0.0);
  }
  tableA_->clear();
}

} /* data */ 

} /* furious */ 

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
