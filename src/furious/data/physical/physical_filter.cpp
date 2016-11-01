

#include "physical_filter.h"

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

  } /* data */ 

} /* furious */ 
