

#include <bf_object.h>
#include <cassert>

namespace tnasdk {

BFObject::BFObject( const std::string& type ) : m_type(type), p_bbox(nullptr) {}

Vector2f BFObject::position() {
  assert( p_bbox != nullptr );
  return p_bbox->position();
}

void  BFObject::position( Vector2f position ) {
  assert( p_bbox != nullptr );
  p_bbox->position(position);
}

float_t BFObject::rotation() {
  assert(p_bbox != nullptr);
  return p_bbox->rotation();
}

void BFObject::rotation( float_t rotation ) {
  assert(p_bbox != nullptr);
  p_bbox->rotation( rotation );
}
  
} /* tnasdk */ 
