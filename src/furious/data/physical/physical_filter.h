

#ifndef _FURIOUS_PHYSICAL_H_
#define _FURIOUS_PHYSICAL_H_

#include "../common.h"
#include "physical_plan.h"

namespace furious
{
  namespace data
  {

    class PhysicalFilter : public IPhysicalOperator {
      public:
        PhysicalFilter( IPhysicalOperatorPtr input );
        virtual ~PhysicalFilter() = default;

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        bool_t has_next() const override;
        IRow* next() override;

      private:

        mutable IPhysicalOperatorPtr input_;
        mutable IRowPtr next_row_;
    };

  } /* data */ 
  
} /* furious */ 
#endif
