

#ifndef _FURIOUS_LOGIC_SCAN_H
#define _FURIOUS_LOGIC_SCAN_H value

#include <data/common.h>
#include <data/logic_plan.h>
#include <sstream>
#include <cassert>

namespace furious {
namespace data {
class LogicScan : public LogicPlanNode {

public:
  LogicScan(TableId table);
  ~LogicScan() = default;

  virtual void accept( LogicPlanVisitor& visitor ) override;

  virtual std::string str() const override; 

  virtual uint32_t num_children() const override; 

  virtual LogicPlanNodePtr child( uint32_t i ) const override;

  TableId m_table;
};

} /* data */ 
} /* furious */ 
#endif
