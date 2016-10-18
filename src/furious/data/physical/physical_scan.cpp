

#include "physical_scan.h"
#include "../database.h"

namespace furious
{
  namespace data
  {

    PhysicalScan::PhysicalScan(TableId table) :
      table_(Database::get_instance()->find_table(table)) {}

    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////

    bool_t PhysicalScan::has_next() const {
    }
    
    IRow* PhysicalScan::next() {
    }

    
  } /* data */ 
} /* furious */ 
