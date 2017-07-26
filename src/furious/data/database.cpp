


#include <data/database.h>

namespace furious {
namespace data {

DatabasePtr Database::get_instance() {
  static DatabasePtr instance(new Database());
  return instance;
}

TableId Database::get_id(const std::string& name) {
  assert(m_table_ids.find(name) != m_table_ids.end());
  if(m_table_ids.find(name) == m_table_ids.end()) return INVALID_ID;
  return m_table_ids.find(name)->second; 
}

TablePtr Database::find_table(TableId id) {
  assert(m_tables.find(id) != m_tables.end());
  if(m_tables.find(id) == m_tables.end()) return nullptr;
  return m_tables.find(id)->second;
}
  
} /* data */ 
} /* furious */ 
