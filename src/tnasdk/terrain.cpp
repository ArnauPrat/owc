

#include <terrain.h>
#include <bbox.h>
#include <tnasdk.h>
#include <collision_engine.h>
#include <bf_object.h>

namespace tnasdk {

Terrain::Terrain() : 
  BFObject("terrain"), 
  p_bbox(nullptr) {
}

Terrain::~Terrain() {
}
  
} /* tnasdk */ 
