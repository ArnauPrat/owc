

#ifndef _FURIOUS_EXECUTION_ENGINE_H_
#define _FURIOUS_EXECUTION_ENGINE_H_

#include "common/types.h"
#include "isystem.h"
#include "database.h"
#include <set>
#include <memory>

namespace furious
{
  namespace data
  {
    class ExecutionEngine {
      using Systems = std::set<std::shared_ptr<ISystem>>;

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
          systems_.insert(sp);
        }

        /**
         * Runs the registered systems
         */
        void run_systems();

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

        Systems                   systems_;     /** Holds the list of registered systems **/
        std::shared_ptr<Database> database_;    /** Pointer to the database **/

    };
  } /* data */ 
  
} /* furious */ 

#endif
