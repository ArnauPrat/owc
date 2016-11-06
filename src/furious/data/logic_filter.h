

#ifndef _FURIOUS_LOGIC_FILTER_H
#define _FURIOUS_LOGIC_FILTER_H 

#include "common.h"
#include "logic_plan.h"
#include <sstream>

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

      virtual std::string str() const { 
        std::stringstream ss;
        ss << "LogicFilter()";
        return ss.str();
      };

      virtual uint32_t num_children() const { return 1; };

      virtual LogicPlanNodePtr child( uint32_t i ) const { 
        assert(i == 0);
        return table_;
      };

      LogicPlanNodePtr table_;
    };
    
  } /* data */ 
  
} /*  furious */ 
#endif
