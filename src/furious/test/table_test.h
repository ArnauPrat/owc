


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
    };

    struct ComponentB {
      uint32_t field1;
      float    field2;
    };

    class TestSystem : public System<ComponentA, ComponentB> {
      public:
        void run( ComponentA& a, ComponentB& b ) const override {
          std::cout << typeid(a).name() << " " << typeid(b).name() << std::endl;
        }
    };


    TEST_F(TableTest,TableWorks) {

      Database database;
      database.create_table<ComponentA>();
      database.create_table<ComponentB>();

      auto tablea = database.find_table<ComponentA>();
      auto tableb = database.find_table<ComponentB>();

      for(int i = 0; i < 100000; ++i) {
        //tablea->insert(1,1.0f);
        tablea->insert();
      }

      ExecutionEngine exec_engine;
      exec_engine.register_system<TestSystem>();

      //ASSERT_TRUE(table.size() == counter);
    }
      
  }
}

