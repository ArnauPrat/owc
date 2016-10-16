

#ifndef _FURIOUS_DATA_H_
#define _FURIOUS_DATA_H_

#include "database.h"
#include "itable.h"
#include "system.h"
#include "table.h"
#include <common/common.h>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>

namespace furious {
  namespace data {

    using TableId = uint32_t;
    using TableMap = std::map<TableId, ITablePtr>;
    using TableMapPair = std::pair<TableId, ITablePtr>;
    using TableIdMap = std::map<std::string, TableId>;
    using TableIdMapPair = std::pair<std::string, TableId>;

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
          TableId id = next_id_++;
          tables_.insert(TableMapPair(id,sp));
          table_ids_.insert(TableIdMapPair(typeid(T).name(),id));
        }

        /**
         * Gets the table with the given name
         */
        template <typename T>
        std::shared_ptr<Table<T>> find_table() {
          return std::dynamic_pointer_cast<Table<T>>(find_table(get_id(typeid(T).name())));
        }

        /**
         * Finds a table based on its id
         */
        ITablePtr find_table(TableId id) {
          return tables_.find(id)->second;
        }

        /**
         * Gets the internal id of a table
         */
        TableId get_id(const std::string& name) {
          return table_ids_.find(name)->second; 
        }


        /**
         * Gets the table from name
         * */
        std::shared_ptr<ITable> find_table( const std::string& str) {
          return tables_.find(get_id(str))->second;
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

        TableMap          tables_;      /** Holds a map between component types and their tables **/
        TableIdMap        table_ids_;   /** Holds a map between table names and ids **/
        TableId           next_id_      = 0;
        static Database*  instance_;
    };
  }
}

#endif


