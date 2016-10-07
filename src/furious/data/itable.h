


#ifndef _FURIOUS_ITABLE_H_
#define _FURIOUS_ITABLE_H_ 

#include "irow.h"
#include "itable_iterator.h"
#include <memory>
#include <type_traits>

namespace furious
{
  namespace data
  {
    class ITable {
      public:
        ITable() = default;
        virtual ~ITable() {}
        /**
         * Gets the name of the table
         */
        virtual std::string table_name() const = 0;

        /**
         * Gets an iterator to the rows of the table
         */
        std::unique_ptr<ITableIterator> iterator() {
          return std::unique_ptr<ITableIterator>(priv_iterator());
        };

        /**
         * Gets the size of the table
         */
        virtual uint32_t size() const = 0; 

      protected:

        /**
         * Gets an iterator to the table. This is for operator covariance on
         * std::unique_ptr
         **/
        virtual ITableIterator* priv_iterator() = 0;

    };
  } /* data */ 
  
} /* furious */ 

#endif

