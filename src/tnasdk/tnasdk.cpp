

#include <common.h>
#include <bbox.h>
#include <tnasdk.h>
#include <cassert>
#include <unit.h>
#include <terrain.h>
#include <iostream>
#include <collision_engine.h>

namespace tnasdk {

CollisionEngine*  cengine = nullptr;
float_t           bat_xmin = 0;
float_t           bat_ymin = 0;
float_t           bat_xmax = 0;
float_t           bat_ymax = 0;

/**
 * @brief Tests whether a box is a inside the battlefield
 *
 * @param width The width of the box
 * @param height The height of the box
 * @param position The position of the box
 * @param angle The rotation of the box
 *
 * @return Returns true if the box is inside the battlefield
 */
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
  assert(cengine->bboxes().size() == 0);
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

Terrain* create_terrain( TerrainFeature type, float_t width, float_t height ) {
  return new Terrain(type, width, height);
}

void destroy_terrain( Terrain* terrain ) {
  delete terrain;
}

/**
 * @brief Tests wether a box can be deployed or not at he given position and
 * rotation
 *
 * @param width     The width of the box
 * @param height    The height of the box
 * @param position  The position of the box
 * @param rotation  The rotation of the box
 *
 * @return 
 */
static bool_t deploy( float_t width, float_t height, Vector2f position, float_t rotation ) {
  if( !inside_battlefield(width, height, position, rotation) ) {
    return false;
  }

  BBox* bbox = cengine->create_bbox(nullptr);
  bbox->width(width);
  bbox->height(height);
  bbox->position(position);
  bbox->rotation(rotation);
  std::vector<Collision> collisions = cengine->detect_collisions();
  bool_t found = false;
  for (const Collision& collision : collisions) {
    if (collision.p_bbox_a == bbox || collision.p_bbox_b == bbox) {
      found = true;
      break;
    }
  }
  cengine->destroy_bbox(bbox);
  return !found;
}

bool_t deploy( BFObject* object, Vector2f position, float_t rotation ) {

  if(!deploy(object->width(), object->height(), position, rotation)) {
    return false;
  }

  float_t offset = 0.0f;

  if( object->m_type == "unit" || 
      (object->m_type == "terrain" && 
       static_cast<Terrain*>(object)->m_feature == TerrainFeature::E_IMPASSABLE)) {
    offset = 1.99f;
  }

  // If we fulfill the unit spacing rule, we can deployt the unit (i.e. attach
  // it a bounding box) with a bbox acounting for the unit spacing
  BBox* bbox = cengine->create_bbox(object);
  bbox->width(object->width() + offset);
  bbox->height(object->height() + offset);
  bbox->position(position);
  bbox->rotation(rotation);
  object->p_bbox = bbox;
  return true;
}

void remove( BFObject* unit ) {
  cengine->destroy_bbox(unit->p_bbox);
  unit->p_bbox = nullptr;
}


bool_t is_valid( BFObject* object, Vector2f position, float_t rotation ) {
  if(deploy( object, position, rotation )) {
    cengine->destroy_bbox(object->p_bbox);
    object->p_bbox = nullptr;
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
