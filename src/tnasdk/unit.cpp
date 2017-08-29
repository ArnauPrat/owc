

#include <collision_engine.h>
#include <bbox.h>
#include <tnasdk.h>
#include <unit.h>
#include <iostream>
#include <cassert>

namespace tnasdk {

Unit::Unit ( TroopType troop_type,
             int32_t num_ranks, 
             int32_t num_files,
             float_t troop_width,
             float_t troop_height) :
  BFObject("unit"),
  m_troop_type(troop_type),
  m_num_ranks(num_ranks),
  m_num_files(num_files),
  m_troop_width(troop_width),
  m_troop_height(troop_height),
  p_bbox(nullptr)
{
  m_troop_mask.resize(m_num_ranks*m_num_files,false);
}

Unit::~Unit () {
}

////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////


Vector2f Unit::position() {
  assert( p_bbox != nullptr );
  return p_bbox->position();
}

void  Unit::position( Vector2f position ) {
  assert( p_bbox != nullptr );
  p_bbox->position(position);
}


float_t Unit::rotation() {
  assert(p_bbox != nullptr);
  return p_bbox->rotation();
}

void Unit::rotation( float_t rotation ) {
  assert(p_bbox != nullptr);
  p_bbox->rotation( rotation );
}

float_t Unit::width() {
  return m_num_files*m_troop_width;
}

float_t Unit::height() {
  return m_num_ranks*m_troop_height;
}



////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////

void attach_bbox(Unit* unit) {
  assert(unit->p_bbox == nullptr);
  unit->p_bbox = cengine->create_bbox(unit);
  unit->p_bbox->width(unit->width());
  unit->p_bbox->height(unit->height());
}

void detach_bbox(Unit* unit) {
  assert(unit->p_bbox != nullptr);
  cengine->destroy_bbox(unit->p_bbox);
  unit->p_bbox = nullptr;
}
  
} /* tnasdk */ 
