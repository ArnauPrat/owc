

#include "physical_scan.h"
#include "../database.h"
#include <cassert>
#include <sstream>

namespace furious
{
  namespace data
  {

    PhysicalScan::PhysicalScan(TablePtr table) :
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

    uint32_t PhysicalScan::num_children()  const  {
      return 0;
    }

    IPhysicalOperatorPtr  PhysicalScan::child(uint32_t i ) const {
      assert(false);
      return nullptr;
    }

    std::string PhysicalScan::str() const  {
      std::stringstream ss;
      ss << "PhysicalScan(" << Database::get_instance()->get_id(table_ptr_->table_name());
      return ss.str();
    }

  } /* data */ 
} /* furious */ 
