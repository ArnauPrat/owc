

#ifndef _FURIOUS_PHYSICAL_MAP_H
#define _FURIOUS_PHYSICAL_MAP_H value

#include "physical_plan.h"
#include "../isystem.h"

namespace furious
{
  namespace data
  {


    class PhysicalMap : public IPhysicalOperator {

      public:

        PhysicalMap(IPhysicalOperatorPtr input, ISystemPtr system); 
        virtual ~PhysicalMap() = default;

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        IRowPtr next() override;

        void open() override;

        void close() override;

      private:
        IPhysicalOperatorPtr    input_;
        ISystemPtr              system_;
    };
    
  } /* data */ 
  
} /* furious */ 
#endif
