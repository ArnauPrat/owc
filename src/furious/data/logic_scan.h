

#ifndef _FURIOUS_LOGIC_SCAN_H
#define _FURIOUS_LOGIC_SCAN_H value

#include "common.h"
#include "logic_plan.h"
#include <sstream>
#include <cassert>

namespace furious
{
  namespace data
  {
    struct LogicScan : public LogicPlanNode {

      LogicScan(TableId table) : table_(table) {}
      ~LogicScan() = default;

      ////////////////////////////////////////////////////
      ////////////////////////////////////////////////////
      ////////////////////////////////////////////////////

      virtual void accept( ILogicPlanVisitor& visitor ) { visitor.visit(*this); };

      virtual std::string str() const { 
        std::stringstream ss;
        ss << "LogicScan(" << table_ << ")";
        return ss.str();
      };

      virtual uint32_t num_children() const { return 0; };

      virtual LogicPlanNodePtr child( uint32_t i ) const { 
        assert(false);
        return nullptr;
      };

      TableId table_;
    };
    
  } /* data */ 
  
} /* furious */ 
#endif
