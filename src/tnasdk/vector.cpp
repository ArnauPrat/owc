
#include <vector.h>

namespace tnasdk {

bool_t operator==(const Vector2f& a, const Vector2f& b) {
 return a.x == b.x && a.y == b.y;
}

bool_t operator!=(const Vector2f& a, const Vector2f& b) {
  return !(a == b);
}
  
} /* tnasdk */ 
