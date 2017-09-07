
#ifndef _FURIOUS_STATIC_SYSTEM_H_
#define _FURIOUS_STATIC_SYSTEM_H_ 

#include "system.h"
#include "table.h"
#include "reflection.h"

#include <typeinfo>
#include <vector>

namespace furious {

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
      m_types{type_name<Components>()...}  {
      }

    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////

    void apply( const std::vector<void*>& components ) override;

    virtual void run( Components&...c ) = 0; 

    std::vector<std::string> components() const override;

    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    //////////////////////////////////////////////// 

  private:

    template<std::size_t...Indices>
      void apply( const std::vector<void*> components, indices<Indices...> );

    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////

    const std::vector<std::string> m_types;
  };


template<typename...Components>
void StaticSystem<Components...>::apply( const std::vector<void*>& components ) {
  apply(components,indices_list<sizeof...(Components)>());
}

template<typename...Components>
std::vector<std::string> StaticSystem<Components...>::components() const {
  return m_types;
}

template<typename...Components>
template<std::size_t...Indices>
void StaticSystem<Components...>::apply( const std::vector<void*> components, 
                                         indices<Indices...> ) {
  run(*(static_cast<Components*>(components[Indices]))...);
}

} /* furious */ 
#endif
