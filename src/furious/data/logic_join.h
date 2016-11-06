

#ifndef _FURIOUS_LOGIC_JOIN_H_
#define _FURIOUS_LOGIC_JOIN_H_

#include "common.h"
#include "logic_plan.h"
#include <memory>
#include <sstream>
#include <cassert>

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

      virtual std::string str() const { 
        std::stringstream ss;
        ss << "LogicJoin()";
        return ss.str();
      };

      virtual uint32_t num_children() const { return 2; };

      virtual LogicPlanNodePtr child( uint32_t i ) const { 
        assert( i < 2 );
        if(i == 0) return left_;
        return right_;
      };

      LogicPlanNodePtr left_;
      LogicPlanNodePtr right_;


    };
  } /* data */ 
} /*  furious */ 
#endif
