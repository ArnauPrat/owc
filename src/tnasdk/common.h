

#ifndef _TNASDK_TYPES_H
#define _TNASDK_TYPES_H 
#include <types.h>
#include <troop_type.h>

namespace tnasdk {

/**
 * @brief A 2D vector of float
 */
struct Vector2f {
  float x;
  float y;
};

/**
 * @brief A 2D vector of uint8_t
 */
struct Vector2u8 {
  uint8_t x;
  uint8_t y;
};
  

} /* tnasdk */ 

#endif /* ifndef _TNASDK_TYPES_H */


