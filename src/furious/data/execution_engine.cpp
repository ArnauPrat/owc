

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

#include <iostream>

namespace furious
{
  namespace data
  {
    void ExecutionEngine::run_systems() const {
      auto logic_plan = build_logic_plan();
      auto physical_plan = build_physical_plan(logic_plan);
      execute_physical_plan(physical_plan);
    }

    void ExecutionEngine::execute_physical_plan(PhysicalPlanPtr physical_plan ) const {
      for(auto root : physical_plan->roots_) {
        std::cout << "ENTRA" << std::endl;
        IRowPtr next_row = root->next();
        while(next_row != nullptr) {
          next_row = root->next();
        }
      }
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

    void ExecutionEngine::clear() {
      systems_.clear();
    }
  } /* data */ 
} /* furious */ 
