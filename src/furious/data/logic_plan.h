


#ifndef _FURIOUS_LOGIC_PLAN_H_
#define _FURIOUS_LOGIC_PLAN_H_ 

#include <memory>
#include <vector>

namespace furious
{
  namespace data
  {
    class LogicPlanNode;
    using LogicPlanNodePtr = std::shared_ptr<LogicPlanNode>;

    /**
     * Helper template to reduce verbosity when using shared pointers
     */
    template <typename T, typename... Args>
    auto MakeLogicPlanNodePtr(Args&&... args)  
    {
      return std::static_pointer_cast<LogicPlanNode>(std::make_shared<T>(std::forward<Args>(args)...));
    }

    /**
     * LogicPlanNode base class
     */
    class LogicPlanNode {

    };

    class LogicPlan;
    using LogicPlanPtr = std::shared_ptr<LogicPlan>;

    /**
     * Class representing a Logic execution plan
     */
    class LogicPlan {
      public:
        std::vector<LogicPlanNodePtr> roots_; // The root node of the logic plan
    };
  } /* data */ 
} /* furious */ 
#endif
