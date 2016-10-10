
#include <common/types.h>
#include <data/database.h>
#include <data/system.h>
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

    class TestSystem : public System<ComponentA, ComponentB> {
      public:
        void run( ComponentA& a, ComponentB& b ) const override {
          a.field1 = b.field1;
          a.field2 = b.field2;
        }
    };


    TEST_F(TableTest,TableWorks) {

      auto database = Database::get_instance();
      database->create_table<ComponentA>();
      database->create_table<ComponentB>();

      auto tablea = database->find_table<ComponentA>();
      auto tableb = database->find_table<ComponentB>();

      for(auto i = 0; i < 100000; ++i) {
        tablea->insert(1,1.0f);
        tableb->insert(2,2.0f);
      }

      auto  exec_engine = ExecutionEngine::get_instance();
      exec_engine->register_system<TestSystem>();

      ASSERT_TRUE(tablea->size() == 100000);
      ASSERT_TRUE(tableb->size() == 100000);

      exec_engine->run_systems();
      for(auto i = 0; i < 100000; ++i) {
        ASSERT_TRUE(tablea->get(i).field1 == 2);
        ASSERT_TRUE(tablea->get(i).field2 == 2.0f);
      }

    }
      
  }
}

