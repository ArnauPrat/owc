

#ifndef _FURIOUS_PHYSICAL_SCAN_H
#define _FURIOUS_PHYSICAL_SCAN_H

#include "physical_plan.h"
#include "../table.h"
#include "../common.h"

namespace furious {

class PhysicalScan : public IPhysicalOperator {

public:

  PhysicalScan(TablePtr table); 
  virtual ~PhysicalScan() = default;

  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////

  IRowPtr next() override;

  void open() override;

  void close() override;

  virtual uint32_t num_children()  const override ;

  virtual IPhysicalOperatorPtr  child(uint32_t i) const override;

  virtual std::string str() const override;

private:
  TablePtr            table_ptr_;
  Table::iterator     iterator_;
};

} /* furious */ 
#endif
