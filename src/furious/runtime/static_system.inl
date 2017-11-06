

namespace furious {

template<typename T, typename...Components>
void StaticSystem<T,Components...>::apply_block( const std::vector<void*>& component_blocks ) {
  apply_block( component_blocks, indices_list<sizeof...(Components)>());
}

template<typename T, typename...Components>
template<std::size_t...Indices>
void StaticSystem<T,Components...>::apply_block( const std::vector<void*>& component_blocks, 
                                         indices<Indices...> ) {
  apply_block(static_cast<Components*>(__builtin_assume_aligned(component_blocks[Indices],32))...);
}

template<typename T, typename...Components>
void StaticSystem<T,Components...>::apply_block(Components* __restrict__ ...components) {
  for (size_t i = 0; i < TABLE_BLOCK_SIZE; ++i) {
    m_system_object.run(&components[i]...);
  }
}

template<typename T, typename...Components>
void StaticSystem<T,Components...>::apply( const std::vector<void*>& components ) {
  apply(components,indices_list<sizeof...(Components)>());
}

template<typename T, typename...Components>
template<std::size_t...Indices>
void StaticSystem<T,Components...>::apply( const std::vector<void*>& components, 
                                         indices<Indices...> ) {
  m_system_object.run((static_cast<Components*>(components[Indices]))...);
}

template<typename T, typename...Components>
std::vector<std::string> StaticSystem<T,Components...>::components() const {
  return m_types;
}

  
} /* furious */ 
