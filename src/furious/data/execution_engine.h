

#ifndef _FURIOUS_EXECUTION_ENGINE_H_
#define _FURIOUS_EXECUTION_ENGINE_H_
#endif

namespace furious
{
  namespace data
  {
    class ExecutionEngine {
      using Systems = std::vector<std::shared_ptr<ISystem>>;

      public:
        ExecutionEngine() = default;
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
          systems_.push_back(sp);
        }

        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
        ////////////////////////////////////////////////////
       
      private:
        Systems   systems_;   /** Holds the list of registered systems **/

    };
  } /* data */ 
  
} /* furious */ 
