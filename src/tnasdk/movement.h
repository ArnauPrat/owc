
#ifndef _TNASDK_MOVEMENT_H_
#define _TNASDK_MOVEMENT_H_

#include "common.h"

namespace tnasdk {

class Unit;

////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////

  /**
   * @brief Struct used to store all the information required to properly
   * perform a movement of a unit into the battlefield
   */
struct Movement {
  const Unit* const     p_unit;             // The unit performing the movement 
  Vector2f              m_start_position;   // The starting position of the movement  
  float_t               m_start_rotation;   // The starting rotation of the movement
  float_t               m_max_distance;     // The maximum distance this movement can move
  bool_t                m_is_valid;         // Whether the unit can start a movement or not (e.g. if it is not in the battlefield, it can't)
};

} /* tnasdk */ 

#endif /* ifndef _TNASDK_MOVEMENT_H_ */
