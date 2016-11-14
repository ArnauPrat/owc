
#ifndef _FURIOUS_REFLECTION_H_
#define _FURIOUS_REFLECTION_H_

#include <string>
#include <cassert>

namespace furious
{
  namespace data
  {

    template <typename T>
      std::string type_name() {
        assert(false);
        return " ";
      }  
    
  } /* data */ 
  
} /* furious */ 

#endif
