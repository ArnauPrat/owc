

#ifndef _FURIOUS_LOGIC_JOIN_H_
#define _FURIOUS_LOGIC_JOIN_H_

#include "common.h"
#include "logic_plan.h"
#include <memory>

namespace  furious
{
  namespace data
  {

    struct LogicJoin : public LogicPlanNode {

      LogicJoin( LogicPlanNodePtr left, LogicPlanNodePtr right ) : 
        left_(left),
        right_(right)
      {}

      virtual ~LogicJoin() = default;

      ////////////////////////////////////////////////////
      ////////////////////////////////////////////////////
      ////////////////////////////////////////////////////

      virtual void accept( ILogicPlanVisitor& visitor ) { visitor.visit(*this); };

      LogicPlanNodePtr left_;
      LogicPlanNodePtr right_;


    };
  } /* data */ 
} /*  furious */ 
#endif
