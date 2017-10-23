

namespace furious {

template<typename T>
  Table<T>::Table() : 
    p_table(nullptr)
{
  p_table = new RawTable(T::name(), sizeof(T));
}

template<typename T>
Table<T>::~Table() {
  delete p_table;
}

template<typename T>
T* Table<T>::get_element( uint32_t id ) {
  return p_table->get_element(id);
}

template<typename T>
void Table<T>::drop_element( uint32_t id ) {
  p_table->drop_element(id);
}

template<typename T>
template<typename...Fields>
void Table<T>::insert_element( uint32_t id, Fields &&...x ) {
  T element(std::forward<Fields>(x)...);
  p_table->insert_element(id, &element);
}

template<typename T>
size_t Table<T>::size() {
  return p_table->size();
}

template<typename T>
std::string Table<T>::table_name() {
  return p_table->table_name();
}
  
} /* furious */ 


