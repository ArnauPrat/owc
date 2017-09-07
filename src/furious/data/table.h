


#ifndef _FURIOUS_TABLE_H_
#define _FURIOUS_TABLE_H_ 

#include "common.h"
#include <map>
#include <memory>
#include <type_traits>
#include <typeindex>
#include <vector>
#include <iterator>

namespace furious {
class Table;
class IRow;
using IRowPtr = IRow*;
class IRow {

public:
  IRow(EntityId id) : m_id(id), 
                      m_enabled(true) {}
  virtual ~IRow() = default;

  /**
   * @brief Gets a specific column of a row
   *
   * @param column The column index to get
   *
   * @return A void pointer to the struct hold in the column
   */
  virtual void* column(uint32_t column) = 0; 

  /**
   * @brief Gets the size of a column 
   *
   * @param column The index of the column to get the size of 
   *
   * @return The size of the column
   */
  virtual uint32_t column_size( uint32_t column) const = 0;


  /**
   * @brief Gets the number of columns of this row
   **/
  virtual uint32_t num_columns() const = 0;

  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  ////////////////////////////////////////////////

  EntityId    m_id;
  bool        m_enabled;
};

using TablePtr = std::shared_ptr<Table>;


class Table {

public:
  class BaseIterator;
  using BaseIteratorPtr = std::shared_ptr<BaseIterator>;
  class BaseIterator {
  public:
    virtual IRowPtr next() = 0;
    virtual BaseIteratorPtr clone() const = 0;
  };

  class iterator : public std::iterator<std::input_iterator_tag, IRow> {
  public:
    explicit iterator(BaseIteratorPtr iter) : 
      iter_(iter), current_(iter_->next()) {}

    iterator(iterator& other) {
      *this = other;
    }

    iterator(iterator&& other) {
      *this = other;
    }

    iterator& operator++() {current_ = iter_->next(); return *this;}
    iterator  operator++(int) {iterator retval = *this; ++(*this); return retval;}
    bool      operator==(iterator other) const {return current_ == other.current_;}
    bool      operator!=(iterator other) const {return !(*this == other);}
    pointer   operator*() const { return current_;  }
    pointer   operator->() const { return current_; }

    iterator& operator=(iterator& other) {
      iter_ = other.iter_->clone();
      current_ = other.current_;
      return *this;
    }

  private:
    std::shared_ptr<BaseIterator> iter_;
    IRowPtr                       current_;
  };

public:
  Table(const std::string& name) : m_name(name) {}
  virtual ~Table() {}

  /**
   * Gets the size of the table
   */
  virtual uint32_t size() const = 0; 

  /**
   * Gets an iterator to the begin of the table
   */
  virtual iterator begin() = 0;

  /**
   * Gets an iterator to the end of the table
   */
  virtual iterator end() = 0;

  /**
   * Clear the table
   */
  virtual void clear() = 0;

  /**
   * Gets the row whose id is the given one
   */
  virtual IRowPtr get_row_by_id(uint32_t id) = 0;

  /**
   * Drops the row whose id is the given one
   */
  virtual void drop_row_by_id(uint32_t id) = 0;

  /**
   * Gets the name of the table
   */
  std::string table_name() { return m_name; };

private:
  std::string m_name;

};

} /* furious */ 

#endif

