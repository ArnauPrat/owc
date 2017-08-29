

#include <common.h>
#include <bbox.h>
#include <tnasdk.h>
#include <cassert>
#include <unit.h>
#include <iostream>
#include <collision_engine.h>

namespace tnasdk {

CollisionEngine*  cengine = nullptr;
float_t           bat_xmin = 0;
float_t           bat_ymin = 0;
float_t           bat_xmax = 0;
float_t           bat_ymax = 0;

static BBox* create_unit_spacing_box(Unit* unit, Vector2f position, float_t rotation) {
  BBox* bbox = cengine->create_bbox();
  bbox->width(unit->width() + 1.90f);
  bbox->height(unit->height() + 1.99f);
  bbox->position(position);
  bbox->rotation(rotation);
  return bbox;
}

////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////

void init_tnasdk( CollisionEngine* cengine_,
                  float_t bwidth,
                  float_t bheight) {
  cengine = cengine_;
  bat_xmin = -bwidth/2.0f;
  bat_ymin = -bheight/2.0f;
  bat_xmax = bwidth/2.0f;
  bat_ymax = bheight/2.0f;
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

static bool_t inside_battlefield( float_t width, 
                                  float_t height, 
                                  Vector2f position, 
                                  float_t angle ) {

  float_t half_width = width / 2.0f;
  float_t half_height = height / 2.0f;

  Vector2f top_right = Vector2f{ half_width, half_height };
  Vector2f top_left = Vector2f{ -half_width, half_height };
  Vector2f bottom_right = Vector2f{ half_width, -half_height };
  Vector2f bottom_left = Vector2f{ -half_width, -half_height };

  Vector2f top_right_r = rotate( top_right, angle ) + position;
  Vector2f top_left_r = rotate( top_left, angle ) + position;
  Vector2f bottom_right_r = rotate( bottom_right, angle) + position;
  Vector2f bottom_left_r = rotate( bottom_left, angle ) + position;

  float_t xmin = std::min( std::min( top_right_r.x, top_left_r.x ), std::min( bottom_right_r.x, bottom_left_r.x ));
  float_t ymin = std::min( std::min( top_right_r.y, top_left_r.y ), std::min( bottom_right_r.y, bottom_left_r.y ));
  float_t xmax = std::max( std::max( top_right_r.x, top_left_r.x ), std::max( bottom_right_r.x, bottom_left_r.x ));
  float_t ymax = std::max( std::max( top_right_r.y, top_left_r.y ), std::max( bottom_right_r.y, bottom_left_r.y ));

  if( xmax > bat_xmax || 
      xmin < bat_xmin ||
      ymax > bat_ymax || 
      ymin < bat_ymin ) {
    return false;
  }

  return true;
}

bool_t deploy( Unit* unit, Vector2f position, float_t rotation ) {
  if( !inside_battlefield(unit->width(), unit->height(), position, rotation) ) {
    return false;
  }

  // We create a bbox which includes the unit spacing
  BBox* margin_bbox = create_unit_spacing_box(unit, position, rotation);
  std::vector<Collision> collisions = cengine->detect_collisions();
  bool_t found = false;
  for (const Collision& collision : collisions) {
    if (collision.p_bbox_a == margin_bbox || collision.p_bbox_b == margin_bbox) {
      found = true;
      break;
    }
  }
  cengine->destroy_bbox(margin_bbox);

  // If we found a collision
  if(found) {
    return false;
  }

  // If we fulfill the unit spacing rule, we can deployt the unit (i.e. attach
  // it a bounding box)
  attach_bbox(unit);
  unit->p_bbox->position(position);
  unit->p_bbox->rotation(rotation);
  return true;
}

void remove( Unit* unit ) {
  detach_bbox(unit);
}

bool_t is_valid( Unit* unit, Vector2f position, float_t rotation ) {
  if(deploy( unit, position, rotation )) {
    detach_bbox(unit);
    return true;
  }
  return false;
}

Movement start_movement(Unit* unit, bool_t marching) {
  return Movement{unit, unit->position(), unit->rotation(), 6.0, false};
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
