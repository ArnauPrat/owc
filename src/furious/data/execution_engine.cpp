

#include "common/types.h"
#include "execution_engine.h"
#include "logic_filter.h"
#include "logic_join.h"
#include "logic_map.h"
#include "logic_scan.h"
#include "physical/physical_plan.h"
#include "physical/physical_scan.h"
#include "physical/physical_filter.h"
#include "physical/physical_hash_join.h"
#include "physical_plan_generator.h"
#include <cstddef>

namespace furious
{
  namespace data
  {
    void ExecutionEngine::run_systems() const {
      /*for(auto system : systems_ ) {
        std::vector<ITablePtr> tables;
        for(auto required_component : system.second->components() ) {
          tables.push_back(database_->find_table(required_component));
        }
        // TODO: Join here between tables
        int count = tables[0]->size();
        std::vector<void*> components(count,nullptr);
        for(int i = 0; i < count; ++i){
          for(uint32_t j = 0; j < tables.size(); ++j) {
           components[j] = tables[j]->get_row(i)->get_data();
          }
          system.second->apply(components);
        }
      }
      */
      auto logic_plan = build_logic_plan();
    }


    SystemPtr ExecutionEngine::get_system(SystemId system) {
      return (*systems_.find(system)).second;
    }

    LogicPlanPtr ExecutionEngine::build_logic_plan() const {
      auto logic_plan = std::make_shared<LogicPlan>();
      for(auto system : systems_ ) {
        if(system.second->components().size() == 1) { // Case when join is not required
          auto logic_scan = MakeLogicPlanNodePtr<LogicScan>(database_->get_id(*system.second->components().begin()));
          auto logic_filter = MakeLogicPlanNodePtr<LogicFilter>(logic_scan);
          auto logic_map = MakeLogicPlanNodePtr<LogicMap>(system.first,logic_filter);
          logic_plan->roots_.push_back(logic_map);
        } else { // Case when we have at least one join
          auto component_iterator = system.second->components().begin();
          auto first_component = *component_iterator++;
          auto second_component = *component_iterator++;
          auto logic_scan_first = MakeLogicPlanNodePtr<LogicScan>(database_->get_id(first_component));
          auto logic_filter_first = MakeLogicPlanNodePtr<LogicFilter>(logic_scan_first);
          auto logic_scan_second = MakeLogicPlanNodePtr<LogicScan>(database_->get_id(second_component));
          auto logic_filter_second = MakeLogicPlanNodePtr<LogicFilter>(logic_scan_second);
          auto previous_join = MakeLogicPlanNodePtr<LogicJoin>(logic_filter_first, logic_filter_second);
          for(;component_iterator != system.second->components().end(); ++component_iterator ) {
            auto next_component = *component_iterator;
            auto logic_scan_next = MakeLogicPlanNodePtr<LogicScan>(database_->get_id(next_component));
            auto logic_filter_next = MakeLogicPlanNodePtr<LogicFilter>(logic_scan_next);
            auto next_join = MakeLogicPlanNodePtr<LogicJoin>(previous_join,logic_filter_next);
            previous_join = next_join;
          }
          auto logic_map = MakeLogicPlanNodePtr<LogicMap>(system.first, previous_join);
          logic_plan->roots_.push_back(logic_map);
        }
      }
      return logic_plan;
    }

    PhysicalPlanPtr  ExecutionEngine::build_physical_plan(LogicPlanPtr logic_plan) const {
      PhysicalPlanGenerator gen;
      PhysicalPlanPtr physical_plan(new PhysicalPlan());
      for(LogicPlanNodePtr node : logic_plan->roots_) {
        node->accept(gen);
        physical_plan->roots_.push_back(gen.get_result());
      }
      return physical_plan;
    }
  } /* data */ 
} /* furious */ 
