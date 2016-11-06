

#include "physical_plan_generator.h"
#include "physical/physical_hash_join.h"
#include "physical/physical_scan.h"
#include "physical/physical_filter.h"
#include "physical/physical_map.h"
#include "database.h"
#include "logic_join.h"
#include "logic_map.h"
#include "logic_scan.h"
#include "logic_filter.h"
#include "execution_engine.h"


namespace furious
{
  namespace data
  {
    void PhysicalPlanGenerator::visit(LogicJoin& logic_join) {
      PhysicalPlanGenerator gen;
      logic_join.left_->accept(gen);
      IPhysicalOperatorPtr left = gen.get_result();
      logic_join.right_->accept(gen);
      IPhysicalOperatorPtr right = gen.get_result();
      result_ = IPhysicalOperatorPtr(new PhysicalHashJoin(left,right));
    }

    void PhysicalPlanGenerator::visit(LogicMap& logic_map) {
      PhysicalPlanGenerator gen;
      ExecutionEnginePtr execution_engine = ExecutionEngine::get_instance();
      logic_map.table_->accept(gen);
    }

    void PhysicalPlanGenerator::visit(LogicScan& logic_scan) {
      PhysicalPlanGenerator gen;
      DatabasePtr database = Database::get_instance();
      TablePtr table = database->find_table(logic_scan.table_);
      result_ = IPhysicalOperatorPtr( new PhysicalScan(table) );
    }

    void PhysicalPlanGenerator::visit(LogicFilter& logic_filter) {
      PhysicalPlanGenerator gen;
      logic_filter.table_->accept(gen);
      result_ = IPhysicalOperatorPtr( new PhysicalFilter(gen.get_result()));
    }

    IPhysicalOperatorPtr PhysicalPlanGenerator::get_result() {
      return result_;
    }
  } /* data */ 
} /* furious */ 
