

#ifndef _FURIOUS_DATABASE_H_
#define _FURIOUS_DATABASE_H_

#include <data/table.h>
#include <data/system.h>
#include <data/static_table.h>
#include <data/common.h>
#include <data/reflection.h>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>
#include <cassert>

namespace furious {
namespace data {

using TableMap = std::map<TableId, TablePtr>;
using TableMapPair = std::pair<TableId, TablePtr>;
using TableIdMap = std::map<std::string, TableId>;
using TableIdMapPair = std::pair<std::string, TableId>;

class Database;
using DatabasePtr = std::shared_ptr<Database>;

class Database {
public:
  Database( const Database& ) = delete;
  Database( Database&& ) = delete;

  virtual ~Database() {} ;

  Database& operator=( const Database& ) = delete;
  Database& operator=( Database&& ) = delete;

  /**
   * Adds an existing table to the database
   */
  template <typename T>
    typename StaticTable<T>::Ptr create_table();

  /**
   * Drops an existing table
   */
  template <typename T>
    void drop_table();

  /**
   * Gets the table from name
   * */
  template <typename T>
    typename StaticTable<T>::Ptr find_table();
  /**
   * Gets the internal id of a table
   */
  template <typename T>
    TableId get_id();

  /**
   * Gets the internal id of a table
   */
  TableId get_id(const std::string& name);

  /**
   * Finds a table based on its id
   */
  TablePtr find_table(TableId id);

  static DatabasePtr get_instance();

protected:
  Database() = default;

private:

  TableMap          m_tables;      /** Holds a map between component types and their tables **/
  TableIdMap        m_table_ids;   /** Holds a map between table names and ids **/
  TableId           m_next_id      = 0;
};

template <typename T>
typename StaticTable<T>::Ptr Database::create_table() {
  assert(m_table_ids.find(type_name<T>()) == m_table_ids.end());
  if(m_table_ids.find(type_name<T>()) != m_table_ids.end()) {
    return nullptr;
  }
  auto table = std::make_shared<StaticTable<T>>(m_next_id, type_name<T>());
  m_tables.insert(TableMapPair(m_next_id,table));
  m_table_ids.insert(TableIdMapPair(type_name<T>(),m_next_id));
  m_next_id++;
  return table; 
}

template <typename T>
void Database::drop_table() {
  assert(m_table_ids.find(type_name<T>()) != m_table_ids.end());
  TableId id = get_id<T>();
  m_tables.erase(id);
  m_table_ids.erase(type_name<T>());
}

template <typename T>
typename StaticTable<T>::Ptr Database::find_table() {
  assert(m_tables.find(get_id<T>()) != m_tables.end());
  if(m_tables.find(get_id<T>()) == m_tables.end()) return nullptr;
  return std::dynamic_pointer_cast<StaticTable<T>>(m_tables.find(get_id<T>())->second);
}

template <typename T>
TableId Database::get_id() {
  assert(m_table_ids.find(type_name<T>()) != m_table_ids.end());
  if(m_table_ids.find(type_name<T>()) == m_table_ids.end()) return INVALID_ID;
  return m_table_ids.find(type_name<T>())->second; 
}

}
}

#endif


