


#include <gtest/gtest.h>
#include "data_test.h"
#include <data/execution_engine.h>
#include <data/physical/physical_map.h>
#include <data/physical/physical_scan.h>

namespace furious
{
  namespace data
  {
    class PhysicalMapTest : public DataTest {
    };

    class TestSystem : public System<ComponentA> {
      public:

        TestSystem() = default;

        void run(ComponentA& component) const override {
          component.field1_ = 4;
          component.field2_ = 4.0;
        }
    };

    TEST_F(PhysicalMapTest, PhysicalMapWorks) {

      for(uint32_t i = 0; i < 10000; ++i) {
        tableA_->insert(i,i*2,i*1.0);
      }

      ExecutionEnginePtr engine = ExecutionEngine::get_instance(); 
      ISystemPtr system = ISystemPtr(new TestSystem());

      IPhysicalOperatorPtr physical_scanA( new PhysicalScan(tableA_));
      IPhysicalOperatorPtr physical_map( new PhysicalMap(physical_scanA, system) );
      physical_map->open();
      IRowPtr row = physical_map->next();
      while(row != nullptr) {
        row = physical_map->next();
      }
      physical_map->close();

      for(auto it = tableA_->begin(); it != tableA_->end(); ++it) {
        ASSERT_EQ(it->get_data().field1_, 4);
        ASSERT_EQ(it->get_data().field2_, 4.0);
      }
    }
    
  } /* data */ 
  
} /* furious */ 

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
