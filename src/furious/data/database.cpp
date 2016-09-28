

#include "database.h"

namespace furious {
  namespace data {

        void Database::add_table(std::shared_ptr<ITable> table) {
          tables_.insert(TableMapPair(table->table_name(), table));
        }

        std::shared_ptr<ITable> Database::find_table(const std::string& table_name) {
          return tables_.find(table_name)->second;
        }
  }
}

