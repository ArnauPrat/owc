

#ifndef _TNASDK_H_
#define _TNASDK_H_ value

#include <common.h>

namespace tnasdk {

class PhysicalFactory;
class Unit;

extern PhysicalFactory* pfactory;

/**
 * @brief Initializes the tnasdk
 *
 * @param pfactory A pointer to a Physical Factory proviging physical unit
 * instances
 */
void init_tnasdk( PhysicalFactory* pfactory );

/**
 * @brief Creates a unit
 *
 * @param troop_type The troop type of the unit
 * @param num_ranks The number of ranks of the unit
 * @param num_files The number of files of the unit
 * @param troop_width The width of the troops forming the unit
 * @param troop_height The height of the troops forming the unit
 *
 * @return  Returns a newly created unit
 */
Unit* create_unit(TroopType troop_type,
                  uint8_t num_ranks, 
                  uint8_t num_files,
                  uint8_t troop_width,
                  uint8_t troop_height);

/**
 * @brief Destroys a given unit
 *
 * @param unit The unit to destroy
 */
void destroy_unit(Unit* unit);


} /* tnasdk */ 


#endif /* ifndef _TNASDK_H_ */
