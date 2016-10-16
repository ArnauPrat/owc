
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

        class Row : public IRow {
          public:

            template<typename...Fields>
            Row ( EntityId id, Fields&&...x) : IRow(id), data_(std::forward<Fields>(x)...) {}

            void* get_data() {
              return &data_;
            }

          private:
            T data_;
        };

        public:
          using table_type = Table;
          using Iterator = typename std::vector<T>::iterator;


          Table() = default;
          Table( const Table & ) = delete;
          Table & operator=( const Table &) = delete;
          Table( Table && ) = delete;
          Table & operator=(Table &&) = delete;

          template<typename...Fields>
          void insert( uint32_t id, Fields &&...x ) {
              data_.emplace_back(id, std::forward<Fields>(x)...);
          }

          /**
           * Gets the ith row of the table
           */
          IRow* get_row( uint32_t row ) override {
            return &data_[row];
          }


          /**
           * Gets an iterator to the elements of the table
           */
          Iterator iterator() {
            return begin(data_);
          }

          /**
           * Gets the size of the table (number of elements) 
           */
          uint32_t size() const override {
            return data_.size();
          }

          /**
           * Gets the name of the table
           */
          virtual std::string table_name() const override {
            return std::string(typeid(T).name());
          }

        private:
          std::vector<Row>    data_;        // vector holding the table data
      };
  } /* data */ 
} /* furious */ 
#endif
