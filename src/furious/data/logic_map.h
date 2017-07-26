

#ifndef _FURIOUS_LOGIC_MAP_H
#define _FURIOUS_LOGIC_MAP_H

#include "common.h"
#include "logic_plan.h"
#include "system.h"
#include <sstream>
#include <cassert>

namespace furious {
namespace data {

struct LogicMap : public LogicPlanNode {

  LogicMap( SystemId system, LogicPlanNodePtr table );
  virtual ~LogicMap() = default;

  virtual void accept( LogicPlanVisitor& visitor ) override; 

  virtual std::string str() const override;

  virtual uint32_t num_children() const override;

  virtual LogicPlanNodePtr child( uint32_t i ) const override; 

  SystemId  m_system;
  LogicPlanNodePtr p_table;

};
} /* data */ 
} /* furious */ 
#endif
