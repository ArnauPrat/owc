

#include <common.h>
#include <bbox.h>
#include <tnasdk.h>
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
  delete unit;
}

bool_t deploy( Unit* unit, Vector2f position, float_t rotation ) {
  unit->p_bbox->enable();
  Vector2f scale{unit->p_bbox->width(), unit->p_bbox->height()};
  Transform transform{position,rotation,scale};
  bool_t result =  unit->p_bbox->transform(transform);
  if(result) {
    unit->p_bbox->disable();
    return false;
  }
  return true;
}

void remove( Unit* unit ) {
  unit->p_bbox->disable();
}

bool_t is_valid( Unit* unit, Vector2f position, float_t rotation ) {
  unit->p_bbox->enable();
  Vector2f scale{unit->p_bbox->width(), unit->p_bbox->height()};
  Transform transform{position,rotation,scale};
  bool_t result = unit->p_bbox->transform(transform);
  unit->p_bbox->disable();
  return !result;
}

Movement start_movement(Unit* unit, bool_t marching) {
  BBox* bbox = unit->p_bbox;
  Transform transform = bbox->transform();
  Vector2f start_position = transform.m_position;
  float_t start_rotation = transform.m_rotation;
  return Movement{unit, start_position, start_rotation, 6.0, false};
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
