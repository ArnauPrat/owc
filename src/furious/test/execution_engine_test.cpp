

#include <gtest/gtest.h> 
#include "data_test.h"
#include <data/static_system.h>
#include <data/execution_engine.h>
#include <data/logic_plan.h>
#include <iostream>

namespace furious
{
  namespace data
  {

    struct ComponentC {
      uint32_t field1_;
      double_t field2_;
      ComponentC(uint32_t field1, double_t field2) : field1_(field1), field2_(field2) {}
    };

    class SystemTest : public DataTest {
    };

    class TestSystemA : public StaticSystem<ComponentA> {
      public:
        TestSystemA(SystemId id) : StaticSystem(id) {}
        virtual ~TestSystemA() = default;

        void run(ComponentA& component) const override {
          component.field1_ = 0;
          component.field2_ = 0.0;
        }
    };

    class TestSystemB : public StaticSystem<ComponentB> {
      public:

        TestSystemB(SystemId id) : StaticSystem(id) {}
        virtual ~TestSystemB() = default;

        void run(ComponentB& component) const override {
          component.field1_ = 1;
          component.field2_ = 1.0;
        }
    };

    class TestSystemAB : public StaticSystem<ComponentA, ComponentB> {
      public:

        TestSystemAB(SystemId id) : StaticSystem(id) {}
        virtual ~TestSystemAB() = default;

        void run(ComponentA& componentA, ComponentB& componentB) const override {
        }
    };

    class TestSystemABC : public StaticSystem<ComponentA, ComponentB, ComponentC> {
      public:

        TestSystemABC(SystemId id) : StaticSystem(id) {}
        virtual ~TestSystemABC() = default;

        void run(ComponentA& componentA, ComponentB& componentB, ComponentC& componentC) const override {
        }
    };

    TEST_F(SystemTest, LogicPlan) {

      DatabasePtr database = Database::get_instance();
      auto tableC = database->create_table<ComponentC>();

      ExecutionEnginePtr execution_engine = ExecutionEngine::get_instance();

      execution_engine->register_system<TestSystemA>();
      execution_engine->register_system<TestSystemB>();
      execution_engine->register_system<TestSystemAB>();
      execution_engine->register_system<TestSystemABC>();

      LogicPlanPtr logic_plan = execution_engine->build_logic_plan(); 
      LogicPlanNodePtr rootA = logic_plan->roots_[0];
      ASSERT_STREQ(rootA->str().c_str(), "LogicMap(0)");
      LogicPlanNodePtr filterA = rootA->child(0);
      ASSERT_STREQ(filterA->str().c_str(), "LogicFilter()");
      LogicPlanNodePtr scanA = filterA->child(0);
      ASSERT_STREQ(scanA->str().c_str(), "LogicScan(0)");

      LogicPlanNodePtr rootB = logic_plan->roots_[1];
      ASSERT_STREQ(rootB->str().c_str(), "LogicMap(1)");
      LogicPlanNodePtr filterB = rootB->child(0);
      ASSERT_STREQ(filterB->str().c_str(), "LogicFilter()");
      LogicPlanNodePtr scanB = filterB->child(0);
      ASSERT_STREQ(scanB->str().c_str(), "LogicScan(1)");

      LogicPlanNodePtr rootAB = logic_plan->roots_[2];
      ASSERT_STREQ(rootAB->str().c_str(), "LogicMap(2)");
      LogicPlanNodePtr joinAB = rootAB->child(0);
      ASSERT_STREQ(joinAB->str().c_str(), "LogicJoin()");

      LogicPlanNodePtr filterAB_left = joinAB->child(0);
      ASSERT_STREQ(filterAB_left->str().c_str(), "LogicFilter()");
      LogicPlanNodePtr scanAB_left = filterAB_left->child(0);
      ASSERT_STREQ(scanAB_left->str().c_str(), "LogicScan(0)");

      LogicPlanNodePtr filterAB_right = joinAB->child(1);
      ASSERT_STREQ(filterAB_right->str().c_str(), "LogicFilter()");
      LogicPlanNodePtr scanAB_right = filterAB_right->child(0);
      ASSERT_STREQ(scanAB_right->str().c_str(), "LogicScan(1)");


      LogicPlanNodePtr rootABC = logic_plan->roots_[3];
      ASSERT_STREQ(rootABC->str().c_str(), "LogicMap(3)");
      LogicPlanNodePtr joinAB_C = rootABC->child(0);
      ASSERT_STREQ(joinAB_C->str().c_str(), "LogicJoin()");
      LogicPlanNodePtr filterC = joinAB_C->child(1);
      ASSERT_STREQ(filterC->str().c_str(), "LogicFilter()");
      LogicPlanNodePtr scanC = filterC->child(0);
      ASSERT_STREQ(scanC->str().c_str(), "LogicScan(2)");
      joinAB = joinAB_C->child(0);
      ASSERT_STREQ(joinAB->str().c_str(), "LogicJoin()");

      filterAB_left = joinAB->child(0);
      ASSERT_STREQ(filterAB_left->str().c_str(), "LogicFilter()");
      scanAB_left = filterAB_left->child(0);
      ASSERT_STREQ(scanAB_left->str().c_str(), "LogicScan(0)");

      filterAB_right = joinAB->child(1);
      ASSERT_STREQ(filterAB_right->str().c_str(), "LogicFilter()");
      scanAB_right = filterAB_right->child(0);
      ASSERT_STREQ(scanAB_right->str().c_str(), "LogicScan(1)");




    }
    
  } /* data */ 
  
} /* furious */ 

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
