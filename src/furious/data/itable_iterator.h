
#ifndef _FURIOUS_ITABLE_ITERATOR_H_
#define _FURIOUS_ITABLE_ITERATOR_H_ 

namespace furious
{
  namespace data
  {
    class ITableIterator {
      public:
        virtual bool has_next() const = 0;
    };
    
  } /* data */ 
  
} /* furious */ 
#endif
