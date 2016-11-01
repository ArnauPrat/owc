

#include "physical_hash_join.h"
#include <functional>

namespace furious
{
  namespace data
  {

    static uint32_t size = 1024;

    PhysicalHashJoin::PhysicalHashJoin(IPhysicalOperatorPtr left, IPhysicalOperatorPtr right) : 
      left_(left),
      right_(right),
      hash_table_(size),
      joined_rows_(size)
      {}

    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////

    IRowPtr PhysicalHashJoin::next() {
      IRowPtr next = right_->next();
      while(next != nullptr) {
        uint32_t position = get_hash_position(next);
        auto candidates = hash_table_[position];
        for(auto it = candidates.begin(); it != candidates.end(); ++it ) {
          if((*it)->get_id() == next->get_id()) {
            auto joined_row = std::make_shared<Row>(next->get_id(), (*it), next);
            joined_rows_.push_back(joined_row);
            return joined_row.get();
          }
        }
        next = right_->next();
      }
      return next;
    }

    void PhysicalHashJoin::open() {
      left_->open();
      IRowPtr next = left_->next();
      while(next != nullptr){
        hash_table_[get_hash_position(next)].push_back(next);
        next = left_->next();
      }
      right_->open();
    }

    void PhysicalHashJoin::close() {
      left_->close();
      right_->close();
    }

    uint32_t PhysicalHashJoin::get_hash_position(IRowPtr row) {
      uint32_t position = std::hash<uint32_t>{}(row->get_id()) % size;
      return position;
    }
    
  } /* data */ 
  
} /* furious
 */ 