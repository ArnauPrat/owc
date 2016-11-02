
#ifndef _FURIOUS_TABLE_H_
#define _FURIOUS_TABLE_H_

#include <vector>
#include <utility>
#include <common/types.h>
#include <iterator>

#include "itable_iterator.h"
#include "itable.h"
#include <cassert>

namespace furious {
  namespace data {

    template<typename T>
      class Table : public ITable {
        class Row : public IRow {
          public:

            template<typename...Fields>
              Row ( EntityId id, Fields&&...x) : IRow(id), data_(std::forward<Fields>(x)...) {}

            virtual ~Row() = default;

            virtual void* get_column(uint32_t column) override {
              assert(column == 0);
              return &data_;
            }

            virtual uint32_t size_of_column( uint32_t column)  override {
              assert(column == 0);
              return sizeof(T);
            }

            virtual uint32_t num_columns() override {
              return 1;
            }

            T& get_data() {
              return data_;
            } 

          private:
            T data_;
        };

        public:
        using table_type = Table;
        using Iterator = typename std::vector<Row>::iterator;
        using Ptr = std::shared_ptr<Table<T>>;


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
        IRowPtr get_row( uint32_t row ) override {
          return &data_[row];
        }


        Iterator begin() {
          return std::begin(data_);
        }

        Iterator end() {
          return std::end(data_);
        }

        uint32_t size() const override {
          return data_.size();
        }

        virtual std::string table_name() const override {
          return std::string(typeid(T).name());
        }

        virtual void clear() override {
          data_.clear();
        }

        private:
        std::vector<Row>    data_;        // vector holding the table data
      };
  } /* data */ 
} /* furious */ 
#endif
