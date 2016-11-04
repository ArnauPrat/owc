


#ifndef _FURIOUS_PHYSICAL_PLAN_GENERATOR_H_
#define _FURIOUS_PHYSICAL_PLAN_GENERATOR_H_

#include "ilogic_plan_visitor.h"
#include "physical/physical_plan.h"

namespace furious
{
  namespace data
  {
    class PhysicalPlanGenerator : public ILogicPlanVisitor {
      public:
        PhysicalPlanGenerator() = default;
        virtual ~PhysicalPlanGenerator() = default;

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        virtual void  visit(LogicJoin& logic_join);
        virtual void  visit(LogicMap& logic_map);
        virtual void  visit(LogicScan& logic_scan);
        virtual void  visit(LogicFilter& logic_filter);

        IPhysicalOperatorPtr get_result(); 

      private:

        IPhysicalOperatorPtr result_;

    };
  } /* data */ 
} /* furious */ 

#endif
