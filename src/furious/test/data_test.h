
#include <gtest/gtest.h>
#include <data/database.h>

namespace furious
{
  namespace data
  {

    struct ComponentA {
      uint32_t field1_;
      double_t field2_;
      ComponentA(uint32_t field1, double_t field2 ) : 
        field1_(field1),
        field2_(field2) 
      {}
    };

    struct ComponentB {
      uint32_t field1_;
      double_t field2_;
      ComponentB(uint32_t field1, double_t field2 ) : 
        field1_(field1),
        field2_(field2) 
      {}
    };

    class DataTest : public ::testing::Test {
      protected:
        virtual void SetUp() {
          database_ = Database::get_instance();
          tableA_ = database_->create_table<ComponentA>();
          tableB_ = database_->create_table<ComponentB>();
        }

        virtual void TearDown() {
          database_->drop_table<ComponentA>();
          database_->drop_table<ComponentB>();
          tableA_ = nullptr;
          tableB_ = nullptr;
        }

        DatabasePtr database_ = nullptr;
        StaticTable<ComponentA>::Ptr tableA_ = nullptr;
        StaticTable<ComponentB>::Ptr tableB_ = nullptr;

    };
  } /* data */ 
  
} /* furious */ 
