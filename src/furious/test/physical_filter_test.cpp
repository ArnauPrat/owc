
#include "test/data_test.h"
#include <data/physical/physical_scan.h>
#include <data/physical/physical_filter.h>

namespace furious
{
  namespace data
  {

    class PhysicalFilterTest : public DataTest {
    };

    TEST_F(PhysicalFilterTest, PhysicalFilterWorks) {

      for(uint32_t i = 0; i < 10000; ++i) {
        tableA_->insert(i,i*2,i*1.0);
      }

      for(auto it = tableA_->begin(); it !=  tableA_->end(); ++it) {
        IRowPtr row = *it;
        row->m_enabled = false;
        ++it;
      }

      IPhysicalOperatorPtr physical_scanA( new PhysicalScan(tableA_));
      IPhysicalOperatorPtr physical_filter( new PhysicalFilter(physical_scanA));

      physical_filter->open();
      IRowPtr row = physical_filter->next();
      ASSERT_NE(row, nullptr);
      uint32_t row_index = 1;
      while(row != nullptr) {
        ComponentA* componentA = static_cast<ComponentA*>(row->column(0));
        ASSERT_EQ(componentA->field1_, row_index*2);
        ASSERT_EQ(componentA->field2_, row_index*1.0);
        row = physical_filter->next();
        row_index+=2;
      }
      physical_filter->close();
      tableA_->clear();
      tableB_->clear();
    }
    
  } /* data */ 
  
} /* furious */ 

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
