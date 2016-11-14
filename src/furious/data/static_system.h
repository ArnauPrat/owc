

#ifndef _FURIOUS_STATIC_SYSTEM_H_
#define _FURIOUS_STATIC_SYSTEM_H_ 

#include "system.h"
#include "table.h"
#include <typeinfo>
#include <vector>
#include "reflection.h"

namespace furious
{
  namespace data
  {

    /** Basic struct to hold the index sequence **/
    template <std::size_t... Indices>
      struct indices {};

    /** Induction case of the indices trick **/
    template <std::size_t N, std::size_t... Is>
      struct build_indices
      : build_indices<N-1, N-1, Is...> {};

    /** Base case of the indices trick **/
    template <std::size_t... Is>
      struct build_indices<0, Is...> : indices<Is...> {};

    template <size_t N>
      using indices_list = build_indices<N>;

    template<typename...Components>
      class StaticSystem : public System {
        public:

          StaticSystem(SystemId id) : System{id},
            types_{type_name<Components>()...}  {
            }

          ////////////////////////////////////////////////////
          ////////////////////////////////////////////////////
          ////////////////////////////////////////////////////


          void apply( std::vector<void*>& components ) const override {
            apply(components,indices_list<sizeof...(Components)>());
          }

          virtual void run( Components&...c ) const = 0; 

          constexpr const std::vector<std::string>& components() const override {
            return types_;
          }

          ////////////////////////////////////////////////////
          ////////////////////////////////////////////////////
          ////////////////////////////////////////////////////

        private:

          template<std::size_t...Indices>
            void apply( std::vector<void*>& components, indices<Indices...> ) const {
              run(*(static_cast<Components*>(components[Indices]))...);
            }

          ////////////////////////////////////////////////////
          ////////////////////////////////////////////////////
          ////////////////////////////////////////////////////

          std::vector<std::string> types_;
      };

  } /* data */ 

} /* furious */ 
#endif
