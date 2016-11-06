

#include "physical_filter.h"
#include <cassert>

namespace furious
{
  namespace data
  {

    PhysicalFilter::PhysicalFilter( IPhysicalOperatorPtr input ) :
      input_(input)
      {

      }

    IRowPtr PhysicalFilter::next() {
      IRowPtr next_row = input_->next();
      while(next_row != nullptr && !next_row->is_enabled()) {
        next_row = input_->next();
      }
      return next_row;
    }

    void PhysicalFilter::open() {
      input_->open();

    }

    void PhysicalFilter::close() {
      input_->close();
    }

    uint32_t PhysicalFilter::num_children()  const  {
      return 0;
    }

    IPhysicalOperatorPtr  PhysicalFilter::child(uint32_t i ) const {
      assert(false);
      return nullptr;
    }

    std::string PhysicalFilter::str() const  {
      return "PhysicalFilter()";
    }

  } /* data */ 

} /* furious */ 
