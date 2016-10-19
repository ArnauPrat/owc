

#include "physical_filter.h"

namespace furious
{
  namespace data
  {

    PhysicalFilter::PhysicalFilter( IPhysicalOperatorPtr input ) :
      input_(input),
      next_row_(nullptr) {

      }

    bool_t PhysicalFilter::has_next() const {
      if(next_row_ == nullptr) {
        while(input_->has_next()) {
          next_row_ = input_->next(); 
          if(next_row_->is_enabled()) {
            return true;
          }
        }
        return false;
      }
      return true;
    }

    IRowPtr PhysicalFilter::next() {
      if(next_row_ == nullptr) {
        has_next();
      }

      IRowPtr to_return = next_row_;
      next_row_ = nullptr;
      return to_return;
    }
    
  } /* data */ 
  
} /* furious */ 
