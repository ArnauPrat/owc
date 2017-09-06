

#ifndef _FURIOUS_DATABASE_H_
#define _FURIOUS_DATABASE_H_

#include "table.h"
#include "system.h"
#include "static_table.h"
#include "common.h"
#include "reflection.h"

#include <map>
#include <memory>
#include <string>
#include <typeinfo>
#include <cassert>
#include <iostream>

namespace furious {
namespace data {

using TableMap = std::map<std::string, TablePtr>;
using TableMapPair = std::pair<std::string, TablePtr>;

class Database;
using DatabasePtr = std::shared_ptr<Database>;

class Database {
public:
  Database( const Database& ) = delete;
  Database( Database&& ) = delete;

  virtual ~Database() {} ;

  Database& operator=( const Database& ) = delete;
  Database& operator=( Database&& ) = delete;

  //////////////////////////////////////////////
  //////////////////////////////////////////////
  //////////////////////////////////////////////

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
   * Gets the table from type 
   * */
  template <typename T>
    typename StaticTable<T>::Ptr find_table();

  /**
   * Gets the table from name
   * */
  TablePtr find_table(const std::string& table_name);

  /**
   * Clears and removes all the tables from the database
   * */
  void clear();

  static DatabasePtr get_instance();

protected:
  Database() = default;

private:

  TableMap          m_tables;      /** Holds a map between component types and their tables **/
};

template <typename T>
typename StaticTable<T>::Ptr Database::create_table() {
  assert(m_tables.find(type_name<T>()) == m_tables.end());
  if(m_tables.find(type_name<T>()) != m_tables.end()) {
    return nullptr;
  }
  auto table = std::make_shared<StaticTable<T>>();
  m_tables.insert(TableMapPair(table->table_name(),table));
  return table; 
}

template <typename T>
void Database::drop_table() {
  auto table = m_tables.find(type_name<T>());
  assert(table != m_tables.end());
  m_tables.erase(table->second->table_name());
}

template <typename T>
typename StaticTable<T>::Ptr Database::find_table() {
  auto table = m_tables.find(type_name<T>());
  if(table == m_tables.end()) return nullptr;
  return std::dynamic_pointer_cast<StaticTable<T>>(table->second);
}

}
}

#endif


