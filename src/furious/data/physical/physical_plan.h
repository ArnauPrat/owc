

#ifndef _FURIOUS_PHYSICAL_PLAN
#define _FURIOUS_PHYSICAL_PLAN 

#include "../common.h"
#include "../itable.h"
#include <memory>
#include <vector>

namespace furious
{
  namespace data
  {

    class IPhysicalOperator;
    using IPhysicalOperatorPtr = std::shared_ptr<IPhysicalOperator>;

    class IPhysicalOperator {
      public:
        IPhysicalOperator() = default;
        virtual ~IPhysicalOperator() = default;

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        virtual void open() = 0;
        virtual void close() = 0;
        virtual bool_t has_next() const = 0;
        virtual IRow* next() = 0;
    };

    /**
     * Helper template to reduce verbosity when using shared pointers
     */
    template <typename T, typename... Args>
    auto MakeIPhysicalOperatorPtr(Args&&... args)  
    {
      return std::static_pointer_cast<IPhysicalOperator>(std::make_shared<T>(std::forward<Args>(args)...));
    }

    class PhysicalPlan {
      public:
        std::vector<IPhysicalOperatorPtr> roots_;
    };
    
  } /* data */ 
  
} /* furious */ 


#endif
