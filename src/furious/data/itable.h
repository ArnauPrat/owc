


#ifndef _FURIOUS_ITABLE_H_
#define _FURIOUS_ITABLE_H_ 

#include "common.h"
#include <map>
#include <memory>
#include <type_traits>
#include <typeindex>
#include <vector>

namespace furious
{
  namespace data
  {
    class ITable;
    class IRow;
    using IRowPtr = IRow*;
    class IRow {
      public:

        IRow( EntityId id) : id_(id), enabled_(true) {}
        virtual ~IRow() = default;

        /**
         * Checks if the row is enabled or not
         */
        bool_t  is_enabled() {
          return enabled_ == true;
        }

        /**
         * Sets the row as enabled
         */
        void enable() {
          enabled_ = true;
        }

        /**
         * Sets the row as disabled
         */
        void disable() {
          enabled_ = false;
        }

        /**
         * Gets the id of the row
         */
        EntityId get_id() {
          return id_;
        }

        /**
         * Gets the specified column of the row
         */
        virtual void* get_column(uint32_t column) = 0; 
        /**
         * Gets the size of the column in bytes
         */
        virtual uint32_t size_of_column( uint32_t column) = 0;

        /**
         * Gets the number of columns of the table*/
        virtual uint32_t num_columns() = 0;
        
      private:
        EntityId    id_;
        bool_t      enabled_;
    };

    using ITablePtr = std::shared_ptr<ITable>;

    class ITable {
      public:
        ITable() = default;
        virtual ~ITable() {}

        /**
         * Gets the name of the table
         */
        virtual std::string table_name() const = 0;

        /**
         * Gets the size of the table
         */
        virtual uint32_t size() const = 0; 

        /**
         * Gets a pointer to the ith element of the table
         * */
        virtual IRowPtr get_row(uint32_t index) = 0;


        /**
         * Clear the table
         */
        virtual void clear() = 0;

    };
  } /* data */ 
  
} /* furious */ 

#endif

