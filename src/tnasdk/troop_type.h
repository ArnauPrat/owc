

#ifndef _TNASDK_TROOP_TYPE_H_
#define _TNASDK_TROOP_TYPE_H_ value

#include "common.h"

namespace tnasdk {

/**
 * @brief Different unit types
 */
enum TroopType : uint8_t {
  E_INFANTRY,
  E_WAR_BEAST,
  E_CAVALRY,
  E_MONSTROUS_INFANTRY,
  E_MONSTROUS_BEAST,
  E_MONSTROUS_CAVALRY,
  E_CHARIOT,
  E_MONSTER,
  E_RIDDEN_MONSTER,
  E_SWARM,
  E_WAR_MACHINE,
  E_NUM_TROOP_TYPES
};

} /* tnasdk */ 
#endif /* ifndef _TNASDK_TROOP_TYPE_H_ */
