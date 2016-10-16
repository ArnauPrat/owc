

#ifndef _FURIOus_ISYSTEM_H
#define _FURIOus_ISYSTEM_H value

#include "itable.h"
#include <vector>

namespace furious
{
  namespace data
  {

    class ISystem {
      public:


        /**
         * Applies the system over the set of components
         **/
        virtual void apply( std::vector<void*>& components ) const = 0;

        /**
         * Gets the list of components this system applies to
         */
        virtual const std::vector<std::string>& components() const = 0;
    };
  } /* data */ 
  
} /* furious */ 



#endif
