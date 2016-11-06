

#include <gtest/gtest.h>
#include <data/physical_plan_generator.h>
#include <data/execution_engine.h>
#include <data/static_system.h>
#include "data_test.h"

namespace furious
{
  namespace data
  {

    class PhysicalPlanGeneratorTest : public DataTest {

    };

    class TestSystem : public StaticSystem<ComponentA> {
      public:
        TestSystem(SystemId id) : StaticSystem(id) {}
        virtual ~TestSystem() = default;

        void run(ComponentA& component) const override {
          component.field1_ = 0;
          component.field2_ = 0.0;
        }
    };

    TEST_F(PhysicalPlanGeneratorTest, PhysicalPlanGeneratorWorks) {

      auto execution_engine = ExecutionEngine::get_instance();
      execution_engine->register_system<TestSystem>();
      auto logic_plan = execution_engine->build_logic_plan();

      PhysicalPlanGenerator gen{};
      auto logic_root = logic_plan->roots_[0];
      logic_root->accept(gen);
      auto physical_root = gen.get_result();

    }
    
  } /* data */ 
  
} /* furious */ 

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
