

#ifndef _FURIOUS_LOGIC_MAP_H
#define _FURIOUS_LOGIC_MAP_H

#include "common.h"
#include "logic_plan.h"
#include "isystem.h"

namespace furious
{

  namespace data
  {

    struct LogicMap : public LogicPlanNode {

      LogicMap( SystemId system, LogicPlanNodePtr table ) : system_(system), table_(table) {}

      SystemId  system_;
      LogicPlanNodePtr table_;

    };
    
  } /* data */ 
  
} /* furious */ 
#endif
