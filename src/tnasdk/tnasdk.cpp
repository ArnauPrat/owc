

#include <common.h>
#include <bbox.h>
#include <tnasdk.h>
#include <cassert>
#include <unit.h>
#include <collision_engine.h>

namespace tnasdk {

CollisionEngine*  cengine = nullptr;
float_t           xmin = 0;
float_t           ymin = 0;
float_t           xmax = 0;
float_t           ymax = 0;

////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////

void init_tnasdk( CollisionEngine* cengine_,
                  uint32_t bwidth,
                  uint32_t bheight) {
  cengine = cengine_;
  xmin = -bwidth/2.0f;
  ymin = -bheight/2.0f;
  xmax = bwidth/2.0f;
  ymax = bheight/2.0f;
}

void release_tnasdk() {
}

Unit* create_unit(TroopType troop_type,
                  int32_t num_ranks, 
                  int32_t num_files,
                  float_t troop_width,
                  float_t troop_height) {

Unit* unit = new Unit(troop_type, 
                      num_ranks,
                      num_files,
                      troop_width,
                      troop_height);
  return unit;
}

void destroy_unit(Unit* unit) {
  assert(unit->p_bbox == nullptr);
  delete unit;
}

bool_t deploy( Unit* unit, Vector2f position, float_t rotation ) {
  attach_bbox(unit);
  if(unit->p_bbox->transform(position, rotation)){
    detach_bbox(unit);
    return false;
  }
  return true;
}

void remove( Unit* unit ) {
  detach_bbox(unit);
}

bool_t is_valid( Unit* unit, Vector2f position, float_t rotation ) {
  BBox* bbox = cengine->create_bbox();
  bbox->width(unit->width());
  bbox->height(unit->height());
  bool_t result = bbox->transform(position, rotation);
  cengine->destroy_bbox(bbox);
  return !result;
}

Movement start_movement(Unit* unit, bool_t marching) {
  /*BBox* bbox = unit->p_bbox;
  Transform transform = bbox->transform();
  Vector2f start_position = transform.m_position;
  float_t start_rotation = transform.m_rotation;
  return Movement{unit, start_position, start_rotation, 6.0, false};
  */
}

bool_t end_movement( const Movement& movement, 
                     Vector2f position, 
                     float_t rotation ) {
  return false;
}

bool_t los( const Unit* from, const Unit* to ) {
  return false;
}

} /* tnask */ 
