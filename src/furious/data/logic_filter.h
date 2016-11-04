

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
      virtual ~LogicFilter() = default;

      ////////////////////////////////////////////////////
      ////////////////////////////////////////////////////
      ////////////////////////////////////////////////////
      
      virtual void accept( ILogicPlanVisitor& visitor ) { visitor.visit(*this); };

      LogicPlanNodePtr table_;


    };
    
  } /* data */ 
  
} /*  furious */ 
#endif
