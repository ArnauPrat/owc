

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

        IRow* next() override;

        void open() override;

        void close() override;

      private:
        IPhysicalOperatorPtr input_;
    };

  } /* data */ 
  
} /* furious */ 
#endif
