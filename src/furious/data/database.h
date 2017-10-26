

#ifndef _FURIOUS_DATABASE_H_
#define _FURIOUS_DATABASE_H_

#include "table.h"
#include "common.h"
#include "reflection.h"

#include <map>
#include <memory>
#include <string>
#include <typeinfo>
#include <cassert>
#include <iostream>

namespace furious {

using TableMap = std::map<std::string, Table*>;
using TableMapPair = std::pair<std::string, Table*>;

class Database {
public:
  Database( const Database& ) = delete;
  Database( Database&& ) = delete;

  virtual ~Database();

  Database& operator=( const Database& ) = delete;
  Database& operator=( Database&& ) = delete;

  //////////////////////////////////////////////
  //////////////////////////////////////////////
  //////////////////////////////////////////////

  /**
   * Adds an existing table to the database
   */
  template <typename T>
  Table* create_table();

  /**
   * Drops an existing table
   */
  template <typename T>
  void drop_table();

  /**
   * Gets the table from type 
   * */
  template <typename T>
  Table* find_table();

  /**
   * Gets the table from name
   * */
  Table* find_table(const std::string& table_name);

  /**
   * Clears and removes all the tables from the database
   * */
  void clear();

  static Database* get_instance();

protected:
  Database() = default;

private:

  TableMap          m_tables;      /** Holds a map between component types and their tables **/
};

template <typename T>
Table* Database::create_table() {
  assert(m_tables.find(type_name<T>()) == m_tables.end());
  if(m_tables.find(type_name<T>()) != m_tables.end()) {
    return nullptr;
  }
  auto table =  new Table(T::name(), sizeof(T));
  m_tables.insert(TableMapPair(table->table_name(),table));
  return table; 
}

template <typename T>
void Database::drop_table() {
  auto table = m_tables.find(type_name<T>());
  assert(table != m_tables.end());
  delete table->second;
  m_tables.erase(table);
}

template <typename T>
Table* Database::find_table() {
  auto table = m_tables.find(type_name<T>());
  if(table == m_tables.end()) return nullptr;
  return static_cast<Table*>(table->second);
}

}

#endif


