


#ifndef _FURIOUS_LOGIC_PLAN_H_
#define _FURIOUS_LOGIC_PLAN_H_ 

#include <memory>
#include <vector>

namespace furious
{
  namespace data
  {
    class LogicPlanNode {

    };

    class LogicPlan {
      public:
        std::vector<std::shared_ptr<LogicPlanNode>> roots_; // The root node of the logic plan
    };
  } /* data */ 
} /* furious */ 
#endif
