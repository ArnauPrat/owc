

#ifndef _FURIOUS_PHYSICAL_SCAN_H
#define _FURIOUS_PHYSICAL_SCAN_H

#include "physical_plan.h"
#include "../table.h"
#include "../common.h"

namespace furious
{
  namespace data
  {

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
        TablePtr   table_ptr_;
        uint32_t    table_size_;
        uint32_t    next_row_index_;
    };
    
  } /* data */ 
  
} /* furious */ 
#endif
