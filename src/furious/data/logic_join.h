

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

      LogicJoin( std::shared_ptr<LogicPlanNode> left, std::shared_ptr<LogicPlanNode> right ) : 
        left_(left),
        right_(right)
      {}

      std::shared_ptr<LogicPlanNode> left_;
      std::shared_ptr<LogicPlanNode> right_;

    };
  } /* data */ 
} /*  furious */ 
#endif
