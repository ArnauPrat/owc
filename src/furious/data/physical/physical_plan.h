

#ifndef _FURIOUS_PHYSICAL_PLAN
#define _FURIOUS_PHYSICAL_PLAN 

#include "../common.h"
#include "iphysical_operator.h"
#include <memory>
#include <vector>

namespace furious
{
  namespace data
  {
    class PhysicalPlan {
      public:
        std::vector<IPhysicalOperatorPtr> roots_;
    };
    
  } /* data */ 
  
} /* furious */ 


#endif
