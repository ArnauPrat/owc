

#ifndef _FURIOUS_PHYSICAL_HASH_JOIN_H
#define _FURIOUS_PHYSICAL_HASH_JOIN_H 

#include "physical_plan.h"
#include "../table.h"
#include "../common.h"

#include <cassert>
#include <map>

namespace furious  {

class PhysicalHashJoin : public IPhysicalOperator {

public:
  class Row : public IRow {
  public:
    Row ( EntityId id, IRowPtr row_left, IRowPtr row_right) : 
      IRow(id),
      row_left_(row_left),
      row_right_(row_right) {}

    virtual ~Row() = default;

    virtual void* column(uint32_t column) override {
      assert(column < num_columns());
      return column < row_left_->num_columns() ? row_left_->column(column) 
                                               : row_right_->column(right_column_index(column));
    }

    virtual uint32_t column_size( uint32_t column) const override {
      assert(column < num_columns());
      return column < row_left_->num_columns() ? row_left_->column_size(column) 
                                               : row_right_->column_size(right_column_index(column));
    }

    virtual uint32_t num_columns() const override {
      return row_left_->num_columns() + row_right_->num_columns();
    }

  private:

    /**
     * @brief Translates the column index of the row to the one of the right row
     *
     * @param column The column index
     *
     * @return The right column index
     */
    uint32_t right_column_index( uint32_t column ) const {
      return column - row_left_->num_columns();
    }

    IRowPtr row_left_;
    IRowPtr row_right_;
  };

public:

  PhysicalHashJoin( IPhysicalOperatorPtr left, IPhysicalOperatorPtr right); 
  virtual ~PhysicalHashJoin() = default;

  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////

  IRowPtr next() override;

  void  open() override;

  void  close() override;

  virtual uint32_t num_children()  const override ;

  virtual IPhysicalOperatorPtr  child(uint32_t i) const override;

  virtual std::string str() const override;

private:

  uint32_t get_hash_position(IRowPtr row);

  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////

  IPhysicalOperatorPtr   left_;
  IPhysicalOperatorPtr   right_;
  std::vector<std::vector<IRowPtr>>     hash_table_;
  std::vector<std::shared_ptr<Row>>     joined_rows_;
};

} /* physical_hash_join */ 
#endif
