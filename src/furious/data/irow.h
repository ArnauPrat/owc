
#ifndef _FURIOUS_IROW_H_
#define _FURIOUS_IROW_H_ 

#include "field.h"
#include <list>

namespace furious
{
  namespace data
  {
    class IRow {
      public:
        virtual std::list<FieldInfo> row_info() = 0;
    };
  } /* data */ 
  
} /* furious */ 
#endif
