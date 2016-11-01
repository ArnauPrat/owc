

#ifndef _FURIOUS_DATA_H_
#define _FURIOUS_DATA_H_

#include "database.h"
#include "itable.h"
#include "system.h"
#include "table.h"
#include "common.h"
#include <map>
#include <memory>
#include <string>
#include <typeinfo>
#include <cassert>

namespace furious {
  namespace data {

    using TableMap = std::map<TableId, ITablePtr>;
    using TableMapPair = std::pair<TableId, ITablePtr>;
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
        typename Table<T>::Ptr create_table() {
          assert(table_ids_.find(typeid(T).name()) == table_ids_.end());
          if(table_ids_.find(typeid(T).name()) != table_ids_.end()) return nullptr;
          auto table = std::make_shared<Table<T>>();
          auto sp = std::static_pointer_cast<ITable>(table);
          TableId id = next_id_++;
          tables_.insert(TableMapPair(id,sp));
          table_ids_.insert(TableIdMapPair(typeid(T).name(),id));
          return table;
        }

        template <typename T>
        void drop_table() {
          assert(table_ids_.find(typeid(T).name()) != table_ids_.end());
          TableId id = get_id(typeid(T).name());
          tables_.erase(id);
          table_ids_.erase(typeid(T).name());
        }

        /**
         * Gets the table with the given name
         */
        template <typename T>
        std::shared_ptr<Table<T>> find_table() {
          assert(table_ids_.find(typeid(T).name()) != table_ids_.end());
          if(table_ids_.find(typeid(T).name()) == table_ids_.end()) return nullptr;
          return std::dynamic_pointer_cast<Table<T>>(find_table(get_id(typeid(T).name())));
        }

        /**
         * Gets the table from name
         * */
        ITablePtr find_table( const std::string& str) {
          assert(tables_.find(get_id(str)) != tables_.end());
          if(tables_.find(get_id(str)) == tables_.end()) return nullptr;
          return tables_.find(get_id(str))->second;
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
        ITablePtr find_table(TableId id) {
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


