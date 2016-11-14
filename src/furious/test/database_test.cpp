
#include <data/database.h>
#include <gtest/gtest.h>

namespace furious
{
  namespace data
  {
    struct Component {
      uint32_t field1_;
      double_t field2_;
      Component(uint32_t field1, double_t field2) : 
        field1_(field1),
        field2_(field2)
      {}

      static std::string name() { return "Component"; }
    };

    template<>
      std::string type_name<Component>() {
        return "Component";
      }

   TEST(DatabaseTest, CreateAndDropTable) {
     auto database = Database::get_instance();
     auto table = database->create_table<Component>();
     ASSERT_NE(table,nullptr);
     database->drop_table<Component>();
     auto table2 = database->find_table<Component>();
     ASSERT_EQ(table2,nullptr);
   }


   TEST(DatabaseTest, FindTable) {
     auto database = Database::get_instance();
     database->create_table<Component>();
     auto table = database->find_table<Component>();
     ASSERT_NE(table,nullptr);
     auto table2 = database->find_table<Component>();
     ASSERT_NE(table2,nullptr);
     auto table3 = database->find_table(database->get_id(table->table_name()));
     ASSERT_NE(table3,nullptr);
     database->drop_table<Component>();
   }

  } /* data */ 
} /* furious */ 

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
