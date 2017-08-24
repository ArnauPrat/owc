
#ifndef _TNASDK_VECTOR_H_
#define _TNASDK_VECTOR_H_ value

#include <types.h>

namespace tnasdk {

/**
 * @brief A 2D vector of float
 */
struct Vector2f {
  float_t x;
  float_t y;
};

bool_t operator==(const Vector2f& a, const Vector2f& b);
bool_t operator!=(const Vector2f& a, const Vector2f& b);

/**
 * @brief A 2D vector of uint8_t
 */
struct Vector2u8 {
  uint8_t x;
  uint8_t y;
};
  
} /* tnasdk */ 

#endif /* ifndef _TNASDK_VECTOR_H_ */
