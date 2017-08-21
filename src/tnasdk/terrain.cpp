

#include <terrain.h>
#include <bbox.h>
#include <tnasdk.h>
#include <collision_engine.h>

namespace tnasdk {

Terrain::Terrain( Transform transform) {
  p_bbox = cengine->create_bbox();
}

Terrain::~Terrain() {
  cengine->destroy_bbox(p_bbox);
}
  
} /* tnasdk */ 
