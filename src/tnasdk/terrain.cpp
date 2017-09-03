

#include <terrain.h>
#include <bbox.h>
#include <tnasdk.h>
#include <collision_engine.h>

namespace tnasdk {

Terrain::Terrain( TerrainFeature type,
                  float_t width,
                  float_t height
                ) :
  BFObject("terrain"),
  m_feature(type),
  m_width(width),
  m_height(height)
{

}

float_t Terrain::width(){
  return m_width;
}

float_t Terrain::height(){
  return m_height;
}

} /* tnasdk */ 
