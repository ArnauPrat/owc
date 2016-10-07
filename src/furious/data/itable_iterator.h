
#ifndef _FURIOUS_ITABLE_ITERATOR_H_
#define _FURIOUS_ITABLE_ITERATOR_H_ 

#include "irow.h"

namespace furious
{
  namespace data
  {
    class ITableIterator {
      public:
        virtual bool has_next() const = 0;
        virtual IRow& next() = 0;
    };
    
  } /* data */ 
  
} /* furious */ 
#endif
