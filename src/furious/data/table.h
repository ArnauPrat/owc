#ifndef _FURIOUS_STATIC_TABLE_H_
#define _FURIOUS_STATIC_TABLE_H_

#include "../common/types.h"
#include "reflection.h"
#include "impl/raw_table.h"

#include <vector>
#include <utility>
#include <iterator>

#include <cassert>

namespace furious {

template<typename T>
  class Table {
  public:

    Table();
    virtual ~Table();
    Table( const Table & ) = delete;
    Table& operator=( const Table &) = delete;
    Table( Table && ) = delete;
    Table& operator=(Table &&) = delete;

    //////////////////////////////////////////////
    //////////////////////////////////////////////
    //////////////////////////////////////////////


    T* get_element( uint32_t id ); 

    void drop_element( uint32_t id ); 

    template<typename...Fields>
      void insert_element( uint32_t id, Fields &&...x ); 

    size_t size(); 

    std::string table_name();

  private:
    RawTable*              p_table;              // vector holding the table data
  };

//template<typename...Fields>
//  void insert_element( uint32_t id, Fields &&...x ) {
//    auto pos = m_id_index.find(id);
//    if(pos == m_id_index.end()) {
//      if(m_free_positions.size() > 0) {
//        uint32_t position = m_free_positions.back();
//        m_free_positions.pop_back();
//        Row row(id, std::forward<Fields>(x)...);
//        m_data[position] = row;
//        m_id_index[id] = position;
//      } else {
//        m_data.emplace_back(id, std::forward<Fields>(x)...);
//        m_id_index[id] = m_data.size() - 1;
//      }
//    } else {
//      Row row(id, std::forward<Fields>(x)...);
//      m_data[pos->second] = row;
//    }
//  }
} 

#include "table.inl"
#endif
