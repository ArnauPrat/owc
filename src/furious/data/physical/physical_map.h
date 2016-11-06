

#ifndef _FURIOUS_PHYSICAL_MAP_H
#define _FURIOUS_PHYSICAL_MAP_H value

#include "physical_plan.h"
#include "../system.h"

namespace furious
{
  namespace data
  {


    class PhysicalMap : public IPhysicalOperator {

      public:

        PhysicalMap(IPhysicalOperatorPtr input, SystemPtr system); 
        virtual ~PhysicalMap() = default;

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
        IPhysicalOperatorPtr    input_;
        SystemPtr              system_;
    };
    
  } /* data */ 
  
} /* furious */ 
#endif
