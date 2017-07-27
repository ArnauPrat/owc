
#include <gtest/gtest.h>
#include <data/static_table.h>
#include <set>

namespace furious {
  namespace data {

    struct Component {
      uint32_t field1_;
      double_t field2_;

      Component(uint32_t field1, double_t field2) : field1_(field1), field2_(field2) {}

      static std::string name() {
        return "Component";
      }

    };

    TEST(TableTest,TableWorks) {

      StaticTable<Component> table;
      for(uint32_t i = 0; i < 10000; ++i) {
        table.insert(i,i,i);
      }

      uint32_t i = 0;
      for(auto iter = table.begin(); iter != table.end(); ++iter) {
        ASSERT_EQ(static_cast<Component*>(iter->get_column(0))->field1_,i);
        ASSERT_EQ(static_cast<Component*>(iter->get_column(0))->field2_,i);
        ++i;
      }

      ASSERT_EQ(table.size(),10000);
      table.clear();
      ASSERT_EQ(table.size(),0);

      std::set<uint32_t> data;

      for(uint32_t i = 0; i < 10000; ++i) {
        table.insert(i,i,i);
        data.insert(i);
      }

      ASSERT_EQ(table.size(),10000);

      for(uint32_t i = 0; i < 5000; ++i) {
        table.drop_row_by_id(i);
        data.erase(i);
      }
      ASSERT_EQ(table.size(),5000);

      for(auto iter = table.begin(); iter != table.end(); ++iter) {
        data.erase(iter->get_id());
      }

      ASSERT_EQ(data.size(), 0);
      ASSERT_EQ(table.size(), 5000);

      IRowPtr row = table.get_row_by_id(7500);
      ASSERT_EQ(row->get_id(), 7500);
    }
  }
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}

