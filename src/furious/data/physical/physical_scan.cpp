

#include "physical_scan.h"
#include "../database.h"

namespace furious
{
  namespace data
  {

    PhysicalScan::PhysicalScan(ITablePtr table) :
      table_ptr_(table),
      table_size_(table_ptr_->size()),
      next_row_index_(0){}

    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    
    IRowPtr PhysicalScan::next() {
      if(next_row_index_ >= table_size_) return nullptr;
      return table_ptr_->get_row(next_row_index_++);
    }

    void PhysicalScan::open() {
    }

    void PhysicalScan::close() {

    }
    
  } /* data */ 
} /* furious */ 
