
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
    class Row : public BaseRow {
    public:

      template<typename...Fields>
        Row ( EntityId id, Fields&&...x) : BaseRow(id), 
                                           m_data(std::forward<Fields>(x)...), 
                                           valid_(true) {}

      virtual ~Row() = default;

      virtual void* column(uint32_t column) override {
        assert(column == 0);
        return &m_data;
      }

      virtual uint32_t column_size( uint32_t column) const override {
        assert(column == 0);
        return sizeof(T);
      }

      virtual uint32_t num_columns() const override {
        return 1;
      }

      T& get_data() {
        return m_data;
      } 

      bool is_valid() { return valid_; }

      void set_valid() { valid_ = true; }

      void set_invalid() { valid_ = false; }

    private:
      T m_data;
      bool valid_;
    };

  public:

    using table_type = StaticTable;

    class Iterator : public Table::IBaseIterator {
    public:
      Iterator( typename std::vector<Row>::iterator begin, 
                typename std::vector<Row>::iterator end ) :
        begin_(begin), end_(end) {}
      virtual ~Iterator() = default;

      virtual BaseRow* next() {

        while(begin_ != end_ && !(*begin_).is_valid()) {
          ++begin_;
        };

        if(begin_ != end_) {
          BaseRow* ret = &(*begin_);
          ++begin_;
          return ret;
        }

        return nullptr;
      };

      virtual std::unique_ptr<Table::IBaseIterator> clone() const {
        return std::unique_ptr<Table::IBaseIterator>(new Iterator(begin_, end_));
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
        auto pos = m_id_index.find(id);
        if(pos == m_id_index.end()) {
          if(m_free_positions.size() > 0) {
            uint32_t position = m_free_positions.back();
            m_free_positions.pop_back();
            Row row(id, std::forward<Fields>(x)...);
            m_data[position] = row;
            m_id_index[id] = position;
          } else {
            m_data.emplace_back(id, std::forward<Fields>(x)...);
            m_id_index[id] = m_data.size() - 1;
          }
        } else {
          Row row(id, std::forward<Fields>(x)...);
          m_data[pos->second] = row;
        }
      }

    BaseRow* get_row_by_id( uint32_t id ) override {
      auto pos = m_id_index.find(id);
      assert(pos != m_id_index.end());
      return &m_data[pos->second];
    }

    void drop_row_by_id( uint32_t id ) override {
      auto pos = m_id_index.find(id);
      assert(pos != m_id_index.end());
      m_data[pos->second].set_invalid();
      m_free_positions.push_back(pos->second);
      m_id_index.erase(id);
    }


    Table::iterator begin() {
      return Table::iterator( std::unique_ptr<IBaseIterator>(new Iterator(std::begin(m_data), std::end(m_data))));
    }

    Table::iterator end() {
      return Table::iterator( std::unique_ptr<IBaseIterator>(new Iterator(std::end(m_data), std::end(m_data))));
    }

    uint32_t size() const override {
      return m_data.size() - m_free_positions.size();
    }

    virtual void clear() override {
      m_free_positions.clear();
      for(uint32_t i = 0; i < m_data.size();++i) {
        m_free_positions.push_back(i);
      }
      m_id_index.clear();
    }

  private:
    std::vector<Row>              m_data;              // vector holding the table data
    std::vector<uint32_t>         m_free_positions;
    std::map<uint32_t, uint32_t>  m_id_index;
  };
} /* furious */ 
#endif
