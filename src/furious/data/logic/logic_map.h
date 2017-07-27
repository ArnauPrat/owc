

#ifndef _FURIOUS_LOGIC_MAP_H
#define _FURIOUS_LOGIC_MAP_H

#include <data/common.h>
#include <data/logic/logic_plan.h>
#include <data/system.h>
#include <sstream>
#include <cassert>

namespace furious {
namespace data {

class LogicMap : public LogicPlanNode {

public:
  LogicMap( SystemId system, LogicPlanNodePtr table );
  virtual ~LogicMap() = default;

  //////////////////////////////////////////////
  //////////////////////////////////////////////
  //////////////////////////////////////////////

  virtual void accept( LogicPlanVisitor& visitor ) override; 

  virtual std::string str() const override;

  virtual uint32_t num_children() const override;

  virtual LogicPlanNodePtr child( uint32_t i ) const override; 

  const SystemId  m_system;
  const LogicPlanNodePtr p_table;

};
} /* data */ 
} /* furious */ 
#endif
