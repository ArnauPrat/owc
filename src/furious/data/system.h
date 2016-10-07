

#ifndef _FURIOUS_SYSTEM_H_
#define _FURIOUS_SYSTEM_H_ 

#include "isystem.h"
#include <typeinfo>

namespace furious
{
  namespace data
  {
    template<typename...Components>
      class System : public ISystem {
        public:

          System() : 
            types_{typeid(Components)...} {
            }

          const std::vector<std::type_info>& components() const override {
            return types_;
          }

        private:
          std::vector<std::type_info> types_;
      };
    
  } /* data */ 
  
} /* furious */ 
#endif
