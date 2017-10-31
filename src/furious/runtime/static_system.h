
#ifndef _FURIOUS_STATIC_SYSTEM_H_
#define _FURIOUS_STATIC_SYSTEM_H_ 

#include "system.h"
#include "../data/table.h"
#include "../data/reflection.h"

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

template<typename T, typename...Components>
  class StaticSystem : public System {
  public:

    template<typename...Args>
    StaticSystem(Args&&...args) : System{0},
      m_types{type_name<Components>()...},
      m_system_object(args...){
      }

    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////

    void apply_block( const std::vector<void*>& component_blocks ) override;

    void apply( const std::vector<void*>& components ) override;

    std::vector<std::string> components() const override;

    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    //////////////////////////////////////////////// 

  private:

    template<std::size_t...Indices>
      void apply_block( const std::vector<void*>& components, indices<Indices...> );

    template<std::size_t...Indices>
      void apply( const std::vector<void*>& components, indices<Indices...> );

    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////

    const std::vector<std::string> m_types;
    T                              m_system_object;
  };

} /* furious */ 

#include "static_system.inl"
#endif
