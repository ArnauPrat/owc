

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
      iterator_(table_ptr_->begin()){}

    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    
    IRowPtr PhysicalScan::next() {
      IRowPtr ret = (*iterator_);
      ++iterator_;
      return ret;
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
      ss << "PhysicalScan(" << Database::get_instance()->get_id(table_ptr_->table_name()) << ")";
      return ss.str();
    }

  } /* data */ 
} /* furious */ 
