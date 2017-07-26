


#ifndef _FURIOUS_PHYSICAL_PLAN_GENERATOR_H_
#define _FURIOUS_PHYSICAL_PLAN_GENERATOR_H_

#include <data/logic_plan_visitor.h>
#include <data/physical/physical_plan.h>

namespace furious
{
  namespace data
  {
    class PhysicalPlanGenerator : public LogicPlanVisitor {
      public:
        PhysicalPlanGenerator() = default;
        virtual ~PhysicalPlanGenerator() = default;

        virtual void  visit(LogicJoin& logic_join) override;
        virtual void  visit(LogicMap& logic_map) override;
        virtual void  visit(LogicScan& logic_scan) override;
        virtual void  visit(LogicFilter& logic_filter) override;

        IPhysicalOperatorPtr get_result(); 

      private:

        IPhysicalOperatorPtr result_;

    };
  } /* data */ 
} /* furious */ 

#endif
