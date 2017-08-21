

#ifndef _TNASDK_TRANSFORM_H_
#define _TNASDK_TRANSFORM_H_ value
namespace tnasdk {

#include <common.h>

struct Transform {
  Vector2f m_position{0.0f, 0.0f};
  float_t  m_rotation{0.0f};
  Vector2f m_scale{1.0f,1.0f};
};
  
} /* tnasdk */ 
#endif /* ifndef _TNASDK_TRANSFORM_H_ */
