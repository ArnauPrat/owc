

#include "physical_scan.h"
#include "../database.h"

namespace furious
{
  namespace data
  {

    PhysicalScan::PhysicalScan(TableId table) :
      table_ptr_(Database::get_instance()->find_table(table)),
      table_size_(table_ptr_->size()),
      next_row_index_(0){}

    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////

    bool_t PhysicalScan::has_next() const {
      return next_row_index_ < table_size_;
    }
    
    IRowPtr PhysicalScan::next() {
      if(next_row_index_ >= table_size_) return nullptr;
      return table_ptr_->get_row(next_row_index_++);
    }
    
  } /* data */ 
} /* furious */ 
