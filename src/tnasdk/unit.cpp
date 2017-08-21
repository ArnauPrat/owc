

#include <collision_engine.h>
#include <bbox.h>
#include <tnasdk.h>
#include <unit.h>
#include <iostream>

namespace tnasdk {

Unit::Unit ( TroopType troop_type,
             int32_t num_ranks, 
             int32_t num_files,
             float_t troop_width,
             float_t troop_height) :
  m_troop_type(troop_type),
  m_num_ranks(num_ranks),
  m_num_files(num_files),
  m_troop_width(troop_width),
  m_troop_height(troop_height)
{
  m_troop_mask.resize(m_num_ranks*m_num_files,false);
  p_bbox = cengine->create_bbox();
  p_bbox->width(m_num_files*m_troop_width);
  p_bbox->height(m_num_ranks*m_troop_height);
}

Unit::~Unit () {
  cengine->destroy_bbox(p_bbox);
}
  
} /* tnasdk */ 
