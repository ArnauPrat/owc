

#ifndef _FURIOus_SYSTEM_H
#define _FURIOus_SYSTEM_H value

#include "../data/table.h"

#include <vector>
#include <memory>

using SystemId = uint32_t;

namespace furious {

class System {
public:
  System(const SystemId id) : m_id(id) {}
  virtual ~System() = default;

  /**
   * @brief Applies the system over the set of components
   *
   * @param components The set of blocks with the components 
   */
  virtual void apply_block( const std::vector<void*>& components_blocks ) = 0;

  virtual void apply( const std::vector<void*>& components ) = 0;

  
  /**
   * @brief Gets the names of the components this system is for
   *
   * @return A vector with the names of the components this system is for
   */
  virtual std::vector<std::string> components() const = 0;

  /**
   * @brief The id of the system.
   */
  const SystemId m_id;

};

} /* furious */ 



#endif
