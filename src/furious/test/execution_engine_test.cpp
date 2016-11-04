

#include <gtest/gtest.h>
#include "data_test.h"
#include <data/execution_engine.h>
#include <data/logic_plan.h>

namespace furious
{
  namespace data
  {

    TEST(ExecutionEngineTest, LogicPlan) {

      ExecutionEnginePtr execution_engine = ExecutionEngine::get_instance();
      LogicPlanPtr logic_plan = execution_engine->build_logic_plan(); 

    }
    
  } /* data */ 
  
} /* furious */ 

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
