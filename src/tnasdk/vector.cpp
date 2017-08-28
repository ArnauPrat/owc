
#include <common.h>
#include <cmath>

namespace tnasdk {

bool_t operator==(const Vector2f& a, const Vector2f& b) {
 return a.x == b.x && a.y == b.y;
}

bool_t operator!=(const Vector2f& a, const Vector2f& b) {
  return !(a == b);
}

Vector2f operator+(const Vector2f& a, const Vector2f& b) {
  return Vector2f{a.x + b.x, a.y + b.y};
}

Vector2f rotate( Vector2f vector, float_t angle ) {
  float_t rads = angle * DEGREES_TO_RADS;
  float_t x = vector.x*std::cos(rads) - vector.y*std::sin(rads);
  float_t y = vector.x*std::sin(rads) + vector.y*std::cos(rads);
  return Vector2f{x,y};
}
  
} /* tnasdk */ 
