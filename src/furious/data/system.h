

#ifndef _FURIOus_SYSTEM_H
#define _FURIOus_SYSTEM_H value

#include "common.h"
#include "table.h"
#include <vector>
#include <memory>

namespace furious
{
  namespace data
  {

    class System;
    using SystemPtr = std::shared_ptr<System>;

    class System {
      public:
        System(SystemId id) : id_(id) {}
        virtual ~System() = default;
        /**
         * Applies the system over the set of components
         **/
        virtual void apply( std::vector<void*>& components ) const = 0;

        /**
         * Gets the list of components this system applies to
         */
        virtual const std::vector<std::string>& components() const = 0;

        /**
         * Gets the id of the system
         */
        SystemId id() { return id_; }

      private:

        SystemId id_;

    };
  } /* data */ 
  
} /* furious */ 



#endif
