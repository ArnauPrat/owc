

#ifndef _FURIOUS_DATABASE_H_
#define _FURIOUS_DATABASE_H_

#include "database.h"
#include "table.h"
#include "system.h"
#include "static_table.h"
#include "common.h"
#include <map>
#include <memory>
#include <string>
#include <typeinfo>
#include <cassert>
#include "reflection.h"

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

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        /**
         * Adds an existing table to the database
         */
        template <typename T>
          typename StaticTable<T>::Ptr create_table() {
            assert(table_ids_.find(type_name<T>()) == table_ids_.end());
            if(table_ids_.find(type_name<T>()) != table_ids_.end()) return nullptr;
            auto table = std::make_shared<StaticTable<T>>(next_id_, T::name());
            tables_.insert(TableMapPair(next_id_,table));
            table_ids_.insert(TableIdMapPair(type_name<T>(),next_id_));
            next_id_++;
            return table; 
          }

        /**
         * Drops an existing table
         */
        template <typename T>
          void drop_table() {
            assert(table_ids_.find(type_name<T>()) != table_ids_.end());
            TableId id = get_id<T>();
            tables_.erase(id);
            table_ids_.erase(type_name<T>());
          }

        /**
         * Gets the table from name
         * */
        template <typename T>
         typename StaticTable<T>::Ptr find_table() {
          assert(tables_.find(get_id<T>()) != tables_.end());
          if(tables_.find(get_id<T>()) == tables_.end()) return nullptr;
          return std::dynamic_pointer_cast<StaticTable<T>>(tables_.find(get_id<T>())->second);
        }

        /**
         * Gets the internal id of a table
         */
        template <typename T>
        TableId get_id() {
          assert(table_ids_.find(type_name<T>()) != table_ids_.end());
          if(table_ids_.find(type_name<T>()) == table_ids_.end()) return INVALID_ID;
          return table_ids_.find(type_name<T>())->second; 
        }

        /**
         * Gets the internal id of a table
         */
        TableId get_id(const std::string& name) {
          assert(table_ids_.find(name) != table_ids_.end());
          if(table_ids_.find(name) == table_ids_.end()) return INVALID_ID;
          return table_ids_.find(name)->second; 
        }

        /**
         * Finds a table based on its id
         */
        TablePtr find_table(TableId id) {
          assert(tables_.find(id) != tables_.end());
          if(tables_.find(id) == tables_.end()) return nullptr;
          return tables_.find(id)->second;
        }


        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        static DatabasePtr get_instance() {
          static DatabasePtr instance(new Database());
          return instance;
        }

      protected:
        Database() = default;

      private:

        TableMap          tables_;      /** Holds a map between component types and their tables **/
        TableIdMap        table_ids_;   /** Holds a map between table names and ids **/
        TableId           next_id_      = 0;
        static Database*  instance_;
    };
  }
}

#endif


