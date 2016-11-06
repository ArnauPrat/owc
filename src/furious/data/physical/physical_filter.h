

#ifndef _FURIOUS_PHYSICAL_H_
#define _FURIOUS_PHYSICAL_H_

#include "../common.h"
#include "physical_plan.h"

namespace furious
{
  namespace data
  {

    class PhysicalFilter : public IPhysicalOperator {
      public:
        PhysicalFilter( IPhysicalOperatorPtr input );
        virtual ~PhysicalFilter() = default;

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        IRow* next() override;

        void open() override;

        void close() override;

        virtual uint32_t num_children()  const override ;

        virtual IPhysicalOperatorPtr  child(uint32_t i) const override;

        virtual std::string str() const override;

      private:
        IPhysicalOperatorPtr input_;
    };

  } /* data */ 
  
} /* furious */ 
#endif
