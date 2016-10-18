

#ifndef _FURIOUS_LOGIC_SCAN_H
#define _FURIOUS_LOGIC_SCAN_H value

#include "common.h"
#include "logic_plan.h"
namespace furious
{
  namespace data
  {
    struct LogicScan : public LogicPlanNode {

      LogicScan(TableId table) : table_(table) {}

      TableId table_;
    };
    
  } /* data */ 
  
} /* furious */ 
#endif
