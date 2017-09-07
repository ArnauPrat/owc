
#ifndef _FURIOUS_STATIC_TABLE_H_
#define _FURIOUS_STATIC_TABLE_H_

#include "../common/types.h"
#include "reflection.h"
#include "table.h"

#include <vector>
#include <utility>
#include <iterator>

#include <cassert>

namespace furious {

template<typename T>
  class StaticTable : public Table {
    class Row : public IRow {
    public:

      template<typename...Fields>
        Row ( EntityId id, Fields&&...x) : IRow(id), 
                                           data_(std::forward<Fields>(x)...), 
                                           valid_(true) {}

      virtual ~Row() = default;

      virtual void* column(uint32_t column) override {
        assert(column == 0);
        return &data_;
      }

      virtual uint32_t column_size( uint32_t column) const override {
        assert(column == 0);
        return sizeof(T);
      }

      virtual uint32_t num_columns() const override {
        return 1;
      }

      T& get_data() {
        return data_;
      } 

      bool is_valid() { return valid_; }

      void set_valid() { valid_ = true; }

      void set_invalid() { valid_ = false; }

    private:
      T data_;
      bool valid_;
    };

  public:

    using table_type = StaticTable;
    using Ptr = std::shared_ptr<StaticTable<T>>;

    class Iterator : public Table::BaseIterator {
    public:
      Iterator( typename std::vector<Row>::iterator begin, typename std::vector<Row>::iterator end ) :
        begin_(begin), end_(end) {}
      virtual ~Iterator() = default;

      virtual IRowPtr next() {

        while(begin_ != end_ && !(*begin_).is_valid()) {
          ++begin_;
        };

        if(begin_ != end_) {
          IRowPtr ret = &(*begin_);
          ++begin_;
          return ret;
        }

        return nullptr;
      };

      virtual Table::BaseIteratorPtr clone() const {
        return Table::BaseIteratorPtr(new Iterator(begin_, end_));
      };

    private:
      typename std::vector<Row>::iterator begin_;
      typename std::vector<Row>::iterator end_;
    };

    StaticTable() : Table(type_name<T>())  {};
    virtual ~StaticTable() = default;
    StaticTable( const StaticTable & ) = delete;
    StaticTable & operator=( const StaticTable &) = delete;
    StaticTable( StaticTable && ) = delete;
    StaticTable & operator=(StaticTable &&) = delete;

    //////////////////////////////////////////////
    //////////////////////////////////////////////
    //////////////////////////////////////////////

    template<typename...Fields>
      void insert( uint32_t id, Fields &&...x ) {
        auto pos = id_index_.find(id);
        if(pos == id_index_.end()) {
          if(free_positions_.size() > 0) {
            uint32_t position = free_positions_.back();
            free_positions_.pop_back();
            Row row(id, std::forward<Fields>(x)...);
            data_[position] = row;
            id_index_[id] = position;
          } else {
            data_.emplace_back(id, std::forward<Fields>(x)...);
            id_index_[id] = data_.size() - 1;
          }
        } else {
          Row row(id, std::forward<Fields>(x)...);
          data_[pos->second] = row;
        }
      }

    IRowPtr get_row_by_id( uint32_t id ) override {
      auto pos = id_index_.find(id);
      assert(pos != id_index_.end());
      return &data_[pos->second];
    }

    void drop_row_by_id( uint32_t id ) override {
      auto pos = id_index_.find(id);
      assert(pos != id_index_.end());
      data_[pos->second].set_invalid();
      free_positions_.push_back(pos->second);
      id_index_.erase(id);
    }


    Table::iterator begin() {
      return Table::iterator(Table::BaseIteratorPtr( new Iterator(std::begin(data_), std::end(data_))));
    }

    Table::iterator end() {
      return Table::iterator(Table::BaseIteratorPtr( new Iterator(std::end(data_), std::end(data_))));
    }

    uint32_t size() const override {
      return data_.size() - free_positions_.size();
    }

    virtual void clear() override {
      free_positions_.clear();
      for(uint32_t i = 0; i < data_.size();++i) {
        free_positions_.push_back(i);
      }
      id_index_.clear();
    }

  private:
    std::vector<Row>              data_;              // vector holding the table data
    std::vector<uint32_t>         free_positions_;
    std::map<uint32_t, uint32_t>  id_index_;
  };
} /* furious */ 
#endif
