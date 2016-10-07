

#ifndef _FURIOUS_DATA_H_
#define _FURIOUS_DATA_H_

#include "database.h"
#include "itable.h"
#include "system.h"
#include "table.h"
#include <map>
#include <memory>
#include <string>
#include <typeinfo>

namespace furious {
  namespace data {
    using Systems = std::vector<std::shared_ptr<ISystem>>;
    using TableMap = std::map<std::type_info, std::shared_ptr<ITable>>;
    using TableMapPair = std::pair<std::type_info, std::shared_ptr<ITable>>;

    class Database {
      public:
        Database() = default;
        Database( const Database& ) = delete;
        Database( Database&& ) = delete;

        virtual ~Database();

        Database& operator=( const Database& ) = delete;
        Database& operator=( Database&& ) = delete;

        /**
         * Adds an existing table to the database
         */
        template <typename T>
        void add_table() {
          tables_.insert(TableMapPair(typeid(T), std::make_shared<Table<T>>()));
        }

        template <typename T, typename...Args>
        void add_system( Args&&...x) {
          systems_.insert(std::make_shared<T>(std::forward<Args>(x)...));
        }

        /**
         * Gets the table with the given name
         */
        template <typename T>
        std::shared_ptr<ITable> find_table() {
          return tables_.find(typeid(T))->second;
        }

      private:
        TableMap  tables_;
        Systems   systems_;
    };
  }
}

#endif


