
#include <utility>

namespace furious {
extern Database* database;
extern Workload* workload;

template<typename TComponent>
  void add_component() {
    assert(database != nullptr);
    database->create_table<TComponent>();
  }

template<typename TComponent>
  void remove_component() {
    assert(database != nullptr);
  }

template<typename TSystem, typename...TArgs>
  void add_system(TArgs&&...args) {
    assert(database != nullptr);
    assert(workload != nullptr);
    workload->add_system<TSystem>(std::forward<TArgs>(args)...);
  }

template<typename TSystem>
  void remove_system() {
    assert(database != nullptr);
    assert(workload != nullptr);
    workload->remove_system<TSystem>();
  }


} /* furious */ 
