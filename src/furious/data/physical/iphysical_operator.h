

#ifndef _FURIOUS_IPHYSICAL_OPERATOR_H_
#define _FURIOUS_IPHYSICAL_OPERATOR_H_

#include "../common.h"
#include <memory>

namespace furious
{
  namespace data
  {
    class IPhysicalOperator;
    using IPhysicalOperatorPtr = std::shared_ptr<IPhysicalOperator>;
    class IPhysicalOperator {
      public:
        virtual void open() = 0;
        virtual void close() = 0;
        virtual bool_t has_next() = 0;
        virtual IRow* next() = 0;
    };
  } /* data */ 
} /* furious */ 
#endif
