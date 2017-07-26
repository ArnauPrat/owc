
#ifndef _FURIOUS_REFLECTION_H_
#define _FURIOUS_REFLECTION_H_

#include <string>
#include <cassert>
#include <iostream>

namespace furious {
namespace data {

template <typename T>
  std::string type_name() {
    return T::name();
  }  
} /* data */ 
} /* furious */ 

#endif
