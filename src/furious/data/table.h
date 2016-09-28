


#ifndef _FURIOUS_TABLE_H_
#define _FURIOUS_TABLE_H_

#include <vector>
#include <utility>
#include <common/types.h>
#include <iterator>

#include "irow.h"
#include "itable_iterator.h"
#include "itable.h"

using std::begin;
using std::cbegin;

namespace furious {
  namespace data {

#define FIELD_IDENTIFIER(fieldname) \
    template<typename Q_T> \
    struct fieldname { \
      Q_T fieldname; \
      using Q_type = Q_T; \
      constexpr static char const *Q_name() { return #fieldname; } \
      Q_T &Q_value() & { return fieldname; } \
      Q_T const &Q_value() const & { return fieldname; } \
      Q_T &&Q_value() && { return fieldname; } \
    };

    template<typename...Fields> 
      class Table : public ITable {
        public:
          using table_type = Table;

          /** Structure representing a row in the table.*/
          struct Row : IRow, Fields... {
            using row_type = Row;
            Row() = default;
            Row(Row const &) = default;
            constexpr Row(typename Fields::Q_type &&...x)
              : IRow(), Fields{x}... {}
            ;

            /**
             * Gets the offset of a field in the row in bytes
             */
            // FIXME relies on undefined behavior, can't be constexpr
            template<typename Field>
              /*constexpr*/ static std::uintptr_t offset_of() {
                return reinterpret_cast<std::uintptr_t>(&static_cast<Row*>(nullptr)->Field::Q_value());
              }

            /**
             * Gets the size of a field in the row
             */
            template<typename Field>
              constexpr static std::size_t size_of() { return sizeof(typename Field::Q_type); }

            /**
             * Gets the name of the gien field
             */
            template<typename Field>
              constexpr static char_t const *name_of() { return Field::Q_name(); }

            /**
             * Applies a function to each field of the row
             */
            template<template<typename T> class Trait, typename Function>
              static void each_field(Function &&f)
              {
                char_t __attribute__((unused)) discard[] = {(
                    f(Fields::Q_name(), offset_of<Fields>(), size_of<Fields>(),
                      Trait<typename Fields::Q_type>::value())
                    ,'\0')...};
              }

            /**
             * Applies a function to the row
             */
            template<typename Function>
              auto apply(Function &&f) & 
              { return f(this->Fields::Q_value()...); }

            /**
             * Applies a function to the row
             */
            template<typename Function>
              auto apply(Function &&f) const & 
              { return f(this->Fields::Q_value()...); }

            /**
             * Applies a function to the row
             */
            template<typename Function>
              auto apply(Function &&f) && 
              { return f(this->Fields::Q_value()...); }

          };

          /**
           * Iterator class
           */
          template<typename T>
          class Iterator : public ITableIterator {

            public:
              Iterator( typename std::vector<Row>::iterator itbegin, typename std::vector<Row>::iterator itend ) :
                it_(itbegin),
                end_(itend)
              {
              }

              virtual ~Iterator() {}

              bool has_next() const override {
                return it_ != end_; 
              }

              T& next() override {
                return (*it_++);
              }
              
            private:
              typename std::vector<Row>::iterator it_;
              typename std::vector<Row>::iterator end_;

          };

          Table(const std::string& table_name) : 
            table_name_(table_name) {
          }

          Table( std::string&& table_name) : 
            table_name_(table_name) {
          }

          Table( const Table & ) = delete;
          Table & operator=( const Table &) = delete;
          Table( Table && ) = delete;
          Table & operator=(Table &&) = delete;

          void insert( typename Fields::Q_type &&...x ) {
            data_.emplace_back(std::forward< typename Fields::Q_type>(x)...);
          }

          Row& get( int32_t row ) & {
            return data_[row];
          }


          /**
           * Gets the ith row of the table
           */
          const Row& get( int32_t row ) const & {
            return data_[row];
          }

          std::string table_name() const override {
            return std::move(table_name_);
          }

          std::unique_ptr<Iterator<Row>> iterator() {
            return std::unique_ptr<Iterator<Row>>(priv_iterator());
          }

          Iterator<Row>* priv_iterator() override {
            return new Iterator<Row>(begin(data_),end(data_)); 
          }


          uint32_t size() const override {
            return data_.size();
          }


        private:
          std::vector<Row>  data_;        // vector holding the table data
          std::string       table_name_;  // the name of the table
      };
  } /* data */ 
} /* furious */ 
#endif
