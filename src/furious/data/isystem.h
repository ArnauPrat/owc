

#ifndef _FURIOus_ISYSTEM_H
#define _FURIOus_ISYSTEM_H value

#include <vector>

namespace furious
{
  namespace data
  {

    class ISystem {
      public:

        virtual void apply( std::vector<ITable*>& tables ) const = 0;

        /**
         * Gets the list of components this system applies to
         */
        virtual const std::vector<std::string>& components() const = 0;
    };
  } /* data */ 
  
} /* furious */ 



#endif
