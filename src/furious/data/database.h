

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
    using TableMap = std::map<std::string, ITablePtr>;
    using TableMapPair = std::pair<std::string, ITablePtr>;

    class Database {
      public:
        Database( const Database& ) = delete;
        Database( Database&& ) = delete;

        virtual ~Database() {} ;

        Database& operator=( const Database& ) = delete;
        Database& operator=( Database&& ) = delete;

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        /**
         * Adds an existing table to the database
         */
        template <typename T>
        void create_table() {
          auto sp = std::static_pointer_cast<ITable>(std::make_shared<Table<T>>());
          tables_.insert(TableMapPair(typeid(T).name(),sp));
        }

        /**
         * Gets the table with the given name
         */
        template <typename T>
        std::shared_ptr<Table<T>> find_table() {
          return std::dynamic_pointer_cast<Table<T>>(tables_.find(typeid(T).name())->second);
        }

        /**
         * Gets the table from name
         * */
        std::shared_ptr<ITable> find_table( const std::string& str) {
          return tables_.find(str)->second;
        }

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        
        static std::shared_ptr<Database> get_instance() {
          static std::shared_ptr<Database> instance(new Database());
          return instance;
        }

      protected:
        Database() = default;
      private:

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        TableMap  tables_;      /** Holds a map between component types and their tables **/
        static Database* instance_;
    };
  }
}

#endif


