
#include <common/types.h>
#include <data/database.h>
#include <data/static_system.h>
#include <data/table.h>
#include <gtest/gtest.h>
#include <data/execution_engine.h>

namespace furious {
  namespace data {
    class TableTest : public ::testing::Test {
      protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
    };

    struct ComponentA {
      uint32_t field1;
      float    field2;
      ComponentA( uint32_t a, float b ) : field1(a), field2(b) {}
    };

    struct ComponentB {
      uint32_t field1;
      float    field2;
      ComponentB( uint32_t a, float b ) : field1(a), field2(b) {}
    };

    class TestSystem : public StaticSystem<ComponentA, ComponentB> {
      public:
        TestSystem(SystemId id) : StaticSystem(id) {}
        virtual ~TestSystem() = default;
        void run( ComponentA& a, ComponentB& b ) const override {
          a.field1 = b.field1;
          a.field2 = b.field2;
        }
    };

    class TestSystemAssert : public StaticSystem<ComponentA, ComponentB> {
      public:
        TestSystemAssert(SystemId id ) : StaticSystem(id) {}
        virtual ~TestSystemAssert() = default;

        void run( ComponentA& a, ComponentB& b ) const override {
          ASSERT_TRUE(a.field1 == b.field1);
          ASSERT_TRUE(a.field2 == b.field2);
        }
    };


    TEST_F(TableTest,TableWorks) {

      auto database = Database::get_instance();

      database->create_table<ComponentA>();
      database->create_table<ComponentB>();

      auto tablea = database->find_table<ComponentA>();
      auto tableb = database->find_table<ComponentB>();

      for(auto i = 0; i < 100000; ++i) {
        tablea->insert(i,1,1.0f);
        tableb->insert(i,2,2.0f);
      }

      auto  exec_engine = ExecutionEngine::get_instance();
      exec_engine->register_system<TestSystem>();
      exec_engine->register_system<TestSystemAssert>();
      exec_engine->run_systems();
    }
      
  }
}

