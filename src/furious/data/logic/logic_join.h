

#ifndef _FURIOUS_LOGIC_JOIN_H_
#define _FURIOUS_LOGIC_JOIN_H_

#include "../common.h"
#include "logic_plan.h"

#include <memory>
#include <sstream>
#include <cassert>

namespace  furious {

class LogicJoin : public LogicPlanNode {

public:
  LogicJoin( LogicPlanNodePtr left, LogicPlanNodePtr right );

  virtual ~LogicJoin() = default;

  //////////////////////////////////////////////
  //////////////////////////////////////////////
  //////////////////////////////////////////////

  virtual void accept( LogicPlanVisitor& visitor ) override;

  virtual std::string str() const override; 

  virtual uint32_t num_children() const override; 

  virtual LogicPlanNodePtr child( uint32_t i ) const override; 

  const LogicPlanNodePtr p_left;
  const LogicPlanNodePtr p_right;

};
} /*  furious */ 
#endif
