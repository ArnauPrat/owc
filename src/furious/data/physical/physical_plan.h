

#ifndef _FURIOUS_PHYSICAL_PLAN
#define _FURIOUS_PHYSICAL_PLAN 

#include "../common.h"
#include "../table.h"
#include <memory>
#include <vector>
#include <string>

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
        virtual IRowPtr next() = 0;
        virtual uint32_t num_children() const = 0;
        virtual IPhysicalOperatorPtr  child(uint32_t i) const = 0;
        virtual std::string str() const = 0;
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
