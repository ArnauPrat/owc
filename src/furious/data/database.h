

#ifndef _FURIOUS_DATA_H_
#define _FURIOUS_DATA_H_

#include <memory>
#include "database.h"
#include "table.h"
#include <map>
#include <string>

namespace furious {
  namespace data {
    using TableMap = std::map<std::string, std::shared_ptr<ITable>>;
    using TableMapPair = std::pair<std::string, std::shared_ptr<ITable>>;

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
        void add_table(std::shared_ptr<ITable>);

        /**
         * Gets the table with the given name
         */
        std::shared_ptr<ITable> find_table(const std::string& );

      private:
        TableMap tables_;
    };
  }
}

#endif


