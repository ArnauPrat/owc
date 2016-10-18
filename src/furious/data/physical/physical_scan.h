

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

        PhysicalScan(TableId table); 
        virtual ~PhysicalScan() = default;

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        bool_t has_next() const override;
        IRow* next() override;

      private:
        ITablePtr table_;
    };
    
  } /* data */ 
  
} /* furious */ 
#endif
