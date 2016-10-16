

#include "common/types.h"
#include "execution_engine.h"
#include <cstddef>

namespace furious
{
  namespace data
  {
    void ExecutionEngine::run_systems() {
      for(auto system : systems_ ) {
        std::vector<ITablePtr> tables;
        for(auto required_component : system->components() ) {
          tables.push_back(database_->find_table(required_component));
        }
        // TODO: Join here between tables
        int count = tables[0]->size();
        std::vector<void*> components(count,nullptr);
        for(int i = 0; i < count; ++i){
          for(uint32_t j = 0; j < tables.size(); ++j) {
           components[j] = tables[j]->get_row(i)->get_data();
          }
          system->apply(components);
        }
      }
    }
  } /* data */ 
} /* furious */ 
