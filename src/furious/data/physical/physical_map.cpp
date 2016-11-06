
#include "physical_map.h"
#include <cassert>
#include <sstream>

namespace furious
{
  namespace data
  {

    PhysicalMap::PhysicalMap( IPhysicalOperatorPtr input, SystemPtr system ) :
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

    uint32_t PhysicalMap::num_children()  const  {
      return 0;
    }

    IPhysicalOperatorPtr  PhysicalMap::child(uint32_t i ) const {
      assert(false);
      return nullptr;
    }

    std::string PhysicalMap::str() const  {
      std::stringstream ss;
      ss << "PhysicalMap(" << system_->id() << ")";
      return ss.str();
    }
    
  } /* data */ 
  
} /* furious */ 
