

#ifndef _FURIOUS_LOGIC_MAP_H
#define _FURIOUS_LOGIC_MAP_H

#include "common.h"
#include "logic_plan.h"
#include "system.h"
#include <sstream>
#include <cassert>

namespace furious
{

  namespace data
  {

    struct LogicMap : public LogicPlanNode {

      LogicMap( SystemId system, LogicPlanNodePtr table ) : system_(system), table_(table) {}
      virtual ~LogicMap() = default;

      ////////////////////////////////////////////////////
      ////////////////////////////////////////////////////
      ////////////////////////////////////////////////////

      virtual void accept( ILogicPlanVisitor& visitor ) { visitor.visit(*this); };

      virtual std::string str() const { 
        std::stringstream ss;
        ss << "LogicMap(" << system_ << ")";
        return ss.str();
      };

      virtual uint32_t num_children() const { return 1; };

      virtual LogicPlanNodePtr child( uint32_t i ) const { 
        assert(i == 0);
        return table_;
      };

      SystemId  system_;
      LogicPlanNodePtr table_;

    };
    
  } /* data */ 
  
} /* furious */ 
#endif
