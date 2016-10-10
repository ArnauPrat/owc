


#ifndef _FURIOUS_ITABLE_H_
#define _FURIOUS_ITABLE_H_ 

#include <memory>
#include <type_traits>
#include <typeindex>

namespace furious
{
  namespace data
  {

    class ITable;

    using ITablePtr = std::shared_ptr<ITable>;
    using ITableId = std::type_index;

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

    };
  } /* data */ 
  
} /* furious */ 

#endif

