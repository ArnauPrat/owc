

#ifndef _FURIOUS_EXECUTION_ENGINE_H_
#define _FURIOUS_EXECUTION_ENGINE_H_

#include "logic_join.h"
#include "logic_plan.h"
#include "common.h"
#include "isystem.h"
#include "database.h"
#include <map>
#include <memory>

namespace furious
{
  namespace data
  {
    class ExecutionEngine {
      using SystemMap = std::map<SystemId, std::shared_ptr<ISystem>>;
      using SystemMapPair = std::pair<SystemId, std::shared_ptr<ISystem>>;

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
        void register_system( Args&&...x) {
          auto sp = std::static_pointer_cast<ISystem>(std::make_shared<T>(std::forward<Args>(x)...));
          systems_.insert(SystemMapPair(next_id_++,sp));
        }

        /**
         * Runs the registered systems
         */
        void run_systems() const ;

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        
        static std::shared_ptr<ExecutionEngine> get_instance() {
          static std::shared_ptr<ExecutionEngine> instance(new ExecutionEngine());
          return instance;
        }


      private:

        /*
         * Constructor
         * */
        ExecutionEngine() : database_(Database::get_instance()) {}

        /*
         * Build the logic plan for the current registered systems
         */
        LogicPlanPtr build_logic_plan() const ;


        SystemId                  next_id_ = 0; /** The next id to assign to a sysstem **/
        SystemMap                 systems_;     /** Holds the list of registered systems **/
        std::shared_ptr<Database> database_;    /** Pointer to the database **/

    };
  } /* data */ 
  
} /* furious */ 

#endif
