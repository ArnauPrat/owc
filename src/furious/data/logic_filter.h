

#ifndef _FURIOUS_LOGIC_FILTER_H
#define _FURIOUS_LOGIC_FILTER_H 

#include "common.h"
#include "logic_plan.h"
#include <sstream>

namespace  furious {
namespace data {

class LogicFilter : public LogicPlanNode {

public:
  LogicFilter(LogicPlanNodePtr table);
  virtual ~LogicFilter() = default;

  virtual void accept( LogicPlanVisitor& visitor );

  virtual std::string str() const override;

  virtual uint32_t num_children() const override;

  virtual LogicPlanNodePtr child( uint32_t i ) const override; 

  const LogicPlanNodePtr p_table;

};

} /* data */ 

} /*  furious */ 
#endif
