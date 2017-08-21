

#include "physical_hash_join.h"
#include <functional>
#include <cassert>

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
          if((*it)->m_id == next->m_id) {
            auto joined_row = std::make_shared<Row>(next->m_id, (*it), next);
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
      uint32_t position = std::hash<uint32_t>{}(row->m_id) % size;
      return position;
    }

    uint32_t PhysicalHashJoin::num_children()  const  {
      return 2;
    }

    IPhysicalOperatorPtr  PhysicalHashJoin::child(uint32_t i ) const {
      assert(i < 2);
      if(i == 0) return left_;
      return right_;
    }

    std::string PhysicalHashJoin::str() const  {
      return "PhysicalHashJoin()";
    }
    
  } /* data */ 
  
} /* furious
 */ 
