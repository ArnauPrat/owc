
#include "physical_map.h"

namespace furious
{
  namespace data
  {

    PhysicalMap::PhysicalMap( IPhysicalOperatorPtr input, ISystemPtr system ) :
      input_(input),
      system_(system)
      {

      }

    IRowPtr PhysicalMap::next() {
      IRowPtr next_row = input_->next();
      while(next_row != nullptr && !next_row->is_enabled()) {
        next_row = input_->next();
      }
      if(next_row != nullptr) {
        std::vector<void*> components;
        for(uint32_t i = 0; i < next_row->num_columns(); ++i) {
          components.push_back(next_row->get_column(i));
        }
        system_->apply(components);
      }
      return next_row;
    }

    void PhysicalMap::open() {
      input_->open();

    }

    void PhysicalMap::close() {
      input_->close();
    }


    
  } /* data */ 
  
} /* furious */ 
