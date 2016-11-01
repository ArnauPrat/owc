

#ifndef _FURIOUS_PHYSICAL_SCAN_H
#define _FURIOUS_PHYSICAL_SCAN_H

#include "physical_plan.h"
#include "../itable.h"
#include "../common.h"

namespace furious
{
  namespace data
  {

    class PhysicalScan : public IPhysicalOperator {

      public:

        PhysicalScan(ITablePtr table); 
        virtual ~PhysicalScan() = default;

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        IRowPtr next() override;

        void open() override;

        void close() override;

      private:
        ITablePtr   table_ptr_;
        uint32_t    table_size_;
        uint32_t    next_row_index_;
    };
    
  } /* data */ 
  
} /* furious */ 
#endif
