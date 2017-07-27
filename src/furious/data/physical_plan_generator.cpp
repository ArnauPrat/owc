

#include <data/physical_plan_generator.h>
#include <data/physical/physical_hash_join.h>
#include <data/physical/physical_scan.h>
#include <data/physical/physical_filter.h>
#include <data/physical/physical_map.h>
#include <data/database.h>
#include <data/logic/logic_join.h>
#include <data/logic/logic_map.h>
#include <data/logic/logic_scan.h>
#include <data/logic/logic_filter.h>
#include <data/execution_engine.h>

namespace furious {
namespace data {

void PhysicalPlanGenerator::visit(LogicJoin& logic_join) {
  PhysicalPlanGenerator gen;
  logic_join.p_left->accept(gen);
  IPhysicalOperatorPtr left = gen.get_result();
  logic_join.p_right->accept(gen);
  IPhysicalOperatorPtr right = gen.get_result();
  p_result = IPhysicalOperatorPtr(new PhysicalHashJoin(left,right));
}

void PhysicalPlanGenerator::visit(LogicMap& logic_map) {
  PhysicalPlanGenerator gen;
  ExecutionEnginePtr execution_engine = ExecutionEngine::get_instance();
  logic_map.p_table->accept(gen);
  p_result = IPhysicalOperatorPtr(new PhysicalMap(gen.get_result(), execution_engine->get_system(logic_map.m_system)));
}

void PhysicalPlanGenerator::visit(LogicScan& logic_scan) {
  PhysicalPlanGenerator gen;
  DatabasePtr database = Database::get_instance();
  TablePtr table = database->find_table(logic_scan.m_table);
  p_result = IPhysicalOperatorPtr( new PhysicalScan(table) );
}

void PhysicalPlanGenerator::visit(LogicFilter& logic_filter) {
  PhysicalPlanGenerator gen;
  logic_filter.p_table->accept(gen);
  p_result = IPhysicalOperatorPtr( new PhysicalFilter(gen.get_result()));
}

IPhysicalOperatorPtr PhysicalPlanGenerator::get_result() {
  return p_result;
}
} /* data */ 
} /* furious */ 
