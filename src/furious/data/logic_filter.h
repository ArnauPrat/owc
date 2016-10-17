

#ifndef _FURIOUS_LOGIC_FILTER_H
#define _FURIOUS_LOGIC_FILTER_H 

#include "common.h"
#include "logic_plan.h"

namespace  furious
{
  namespace data
  {

    struct LogicFilter : public LogicPlanNode {

      LogicFilter(std:smart_ptr<LogicPlanNode> table) : table_(table) {}

      std::shared_ptr<LogicPlanNode> table_;

    };
    
  } /* data */ 
  
} /*  furious */ 
#endif
