
#ifndef _FURIOUS_TABLE_H_
#define _FURIOUS_TABLE_H_

#include <vector>
#include <utility>
#include <common/types.h>
#include <iterator>

#include "itable_iterator.h"
#include "itable.h"

using std::begin;
using std::cbegin;

namespace furious {
  namespace data {

    template<typename T>
      class Table : public ITable {
        public:
          using table_type = Table;
          using Iterator = typename std::vector<T>::iterator;


          Table() = default;
          Table( const Table & ) = delete;
          Table & operator=( const Table &) = delete;
          Table( Table && ) = delete;
          Table & operator=(Table &&) = delete;

          template<typename...Fields>
            void insert( Fields &&...x ) {
              data_.emplace_back(std::forward< typename Fields::Q_type>(x)...);
            }

          /**
           * Gets the ith row of the table
           */
          T& get( int32_t row ) & {
            return data_[row];
          }

          /**
           * Gets the ith row of the table
           */
          const T& get( int32_t row ) const & {
            return data_[row];
          }

          uint32_t size() const {
            return data_.size();
          }

        private:
          std::vector<T>    data_;        // vector holding the table data
      };
  } /* data */ 
} /* furious */ 
#endif
