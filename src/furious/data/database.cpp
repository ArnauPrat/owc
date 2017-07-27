


#include <data/database.h>

namespace furious {
namespace data {

DatabasePtr Database::get_instance() {
  static DatabasePtr instance(new Database());
  return instance;
}

TablePtr Database::find_table(const std::string& table_name) {
  assert(m_tables.find(table_name) != m_tables.end());
  auto table = m_tables.find(table_name);
  if(table == m_tables.end()) return nullptr;
  return table->second;
}

void Database::clear() {
  m_tables.clear();
}
  
} /* data */ 
} /* furious */ 
