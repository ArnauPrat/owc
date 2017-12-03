
#include "database.h"
#include <cassert>
#include <utility>

namespace furious  {

template<typename TComponent, typename...Args>
  void Entity::add_component(Args&&...args) {

    Database* database = Database::get_instance();
    Table* table = database->find_table<TComponent>();
    assert(table != nullptr);

    table->insert_element<TComponent>(m_id, std::forward<Args...>(args)...);

  }

template<typename TComponent, typename...Args>
  void Entity::remove_component() {

    Database* database = Database::get_instance();
    Table* table = database->find_table<TComponent>();
    assert(table != nullptr);

  }

} /* furious  */ 

