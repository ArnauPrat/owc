

#ifndef _FURIOUS_LOGIC_FILTER_H
#define _FURIOUS_LOGIC_FILTER_H 

#include "common.h"
#include "logic_plan.h"

namespace  furious
{
  namespace data
  {

    struct LogicFilter : public LogicPlanNode {

      LogicFilter(LogicPlanNodePtr table) : table_(table) {}

      LogicPlanNodePtr table_;

    };
    
  } /* data */ 
  
} /*  furious */ 
#endif
