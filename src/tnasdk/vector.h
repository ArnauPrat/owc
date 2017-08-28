
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
Vector2f operator+(const Vector2f& a, const Vector2f& b);

/**
 * @brief Rotates a vector a given angle (counter clockwise)
 *
 * @param vector The vector to rotate
 * @param angle The angle to rotate in degrees
 *
 * @return  Returns the vector rotated.
 */
Vector2f rotate( Vector2f vector, float_t angle );
  
} /* tnasdk */ 

#endif /* ifndef _TNASDK_VECTOR_H_ */
