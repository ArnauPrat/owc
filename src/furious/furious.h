

#ifndef _FURIOUS_H_
#define _FURIOUS_H_ value

#include "common/common.h"
#include "memory/memory.h"
#include "data/data.h"
#include "runtime/runtime.h"

namespace furious {

/**
 * @brief Initializes the Furious library
 */
void init();

/**
 * @brief Releases the resources of the furious library
 */
void release();

/**
 * @brief Adds a component to the furious framework
 *
 * @tparam TComponent The component to add
 */
template<typename TComponent>
void add_component();

/**
 * @brief Removes a component from the furious framework
 *
 * @tparam TComponent The component to remove 
 */
template<typename TComponent>
void remove_component();

/**
 * @brief Adds a system to the furious framework
 *
 * @tparam typename TSystem The system to add to the furious framework
 * @tparam typename...TArgs The arguments to initialize the system with 
 */
template<typename TSystem, typename...TArgs> 
void add_system(TArgs&&...);

/**
 * @brief Removes a System from the furious framework
 *
 * @tparam TSystem The system to remove from the furious framework
 */
template<typename TSystem>
void remove_system();
  
} /* furious */ 

#include "furious.inl"

#endif /* ifndef _FURIOUS_H_ */
