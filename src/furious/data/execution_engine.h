

#ifndef _FURIOUS_EXECUTION_ENGINE_H_
#define _FURIOUS_EXECUTION_ENGINE_H_

#include "logic_join.h"
#include "logic_plan.h"
#include "common.h"
#include "system.h"
#include "database.h"
#include "physical/physical_plan.h"
#include <map>
#include <memory>

namespace furious
{
  namespace data
  {
    class ExecutionEngine;
    using ExecutionEnginePtr = std::shared_ptr<ExecutionEngine>;
    class ExecutionEngine {
      using SystemMap = std::map<SystemId, SystemPtr>;
      using SystemMapPair = std::pair<SystemId, SystemPtr>;

      public:
        ExecutionEngine( const ExecutionEngine& ) = delete;
        ExecutionEngine( ExecutionEngine&& ) = delete;

        virtual ~ExecutionEngine(){};

        ExecutionEngine& operator=( const ExecutionEngine& ) = delete;
        ExecutionEngine& operator=( ExecutionEngine&& ) = delete;

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////

        /**
         * Adds a system into the the execution engine
         * */
        template <typename T, typename...Args>
        SystemId register_system(Args&&...x) {
          auto sp = std::static_pointer_cast<System>(std::make_shared<T>(next_id_,std::forward<Args>(x)...));
          systems_.insert(SystemMapPair(next_id_,sp));
          return next_id_++;
        }

        /**
         * Runs the registered systems
         */
        void run_systems() const ;

        /**
         * Gets the specified system
         **/
        SystemPtr get_system(SystemId system);

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        
        static std::shared_ptr<ExecutionEngine> get_instance() {
          static ExecutionEnginePtr instance(new ExecutionEngine());
          return instance;
        }

        /*
         * Build the logic plan for the current registered systems
         */
        LogicPlanPtr build_logic_plan() const ;


        /**
         * Builds a physical plan out of a logic plan
         */
        PhysicalPlanPtr  build_physical_plan(LogicPlanPtr logic_plan) const;


        /**
         * Executes the given physical plan
         */
        void execute_physical_plan(PhysicalPlanPtr physical_plan ) const;

      private:

        /*
         * Constructor
         * */
        ExecutionEngine() : database_(Database::get_instance()) {}


        SystemId                  next_id_ = 0; /** The next id to assign to a sysstem **/
        SystemMap                 systems_;     /** Holds the list of registered systems **/
        std::shared_ptr<Database> database_;    /** Pointer to the database **/
    };
  } /* data */ 
  
} /* furious */ 

#endif
