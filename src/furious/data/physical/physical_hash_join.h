

#ifndef _FURIOUS_PHYSICAL_HASH_JOIN_H
#define _FURIOUS_PHYSICAL_HASH_JOIN_H 

#include "physical_plan.h"
#include "../itable.h"
#include "../common.h"
#include <cassert>
#include <map>

namespace furious 
{
  namespace data
  {
    class PhysicalHashJoin : public IPhysicalOperator {

      public:
        class Row : public IRow {
          public:
            Row ( EntityId id, IRowPtr row_left, IRowPtr row_right) : 
              IRow(id),
              row_left_(row_left),
              row_right_(row_right) {}

            virtual ~Row() = default;

            virtual void* get_column(uint32_t column) override {
              assert(column < num_columns());
              return column < row_left_->num_columns() ? row_left_->get_column(column) : row_right_->get_column(get_right_column(column));
            }

            virtual uint32_t size_of_column( uint32_t column)  override {
              assert(column < num_columns());
              return column < row_left_->num_columns() ? row_left_->size_of_column(column) : row_right_->size_of_column(get_right_column(column));
            }

            virtual uint32_t num_columns() override {
              return row_left_->num_columns() + row_right_->num_columns();
            }

          private:
            uint32_t get_right_column( uint32_t column ) {
              return column - row_left_->num_columns();
            }

            IRowPtr row_left_;
            IRowPtr row_right_;
        };

      public:

        PhysicalHashJoin( IPhysicalOperatorPtr left, IPhysicalOperatorPtr right); 
        virtual ~PhysicalHashJoin() = default;

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        IRowPtr next() override;

        void  open() override;

        void  close() override;

      private:

        uint32_t get_hash_position(IRowPtr row);

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
         
        IPhysicalOperatorPtr   left_;
        IPhysicalOperatorPtr   right_;
        std::vector<std::vector<IRowPtr>>     hash_table_;
        std::vector<std::shared_ptr<Row>>     joined_rows_;
    };
    
  } /* data */ 
  
} /* physical_hash_join */ 
#endif
