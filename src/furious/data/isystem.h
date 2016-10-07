

#ifndef _FURIOus_ISYSTEM_H
#define _FURIOus_ISYSTEM_H value

#include <vector>

namespace furious
{
  namespace data
  {

    class ISystem {
      public:
        virtual const std::vector<std::type_info>& components() const = 0;
    };
  } /* data */ 
  
} /* furious */ 



#endif
