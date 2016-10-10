

#include "execution_engine.h"

namespace furious
{
  namespace data
  {

    void ExecutionEngine::run_systems() {
      for(auto system : systems_ ) {
        std::vector<std::shared_ptr<ITable>> tables;
        for(auto required_component : system->components() ) {
          tables.push_back(database_->find_table(required_component));
        }
        system->apply(tables);
      }
    }

  } /* data */ 

} /* furious */ 
