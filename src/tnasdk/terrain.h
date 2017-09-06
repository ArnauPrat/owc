


#ifndef _TNASDK_TERRAIN_H_
#define _TNASDK_TERRAIN_H_

#include "common.h"
#include "troop_type.h"
#include "transform.h"
#include "bf_object.h"

namespace tnasdk {

class BBox;

////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////

enum class TerrainFeature {
  E_IMPASSABLE,
  E_FIELD,
  E_HILL,
  E_FOREST,
  E_RUINS,
  E_WALL,
  E_BUILDING
};

enum class CoverType {
  E_SOFT,
  E_HARD,
  E_NO_COVER
};

struct CoverModifier {
  CoverType m_type;
  Footprint m_footprint;
};

struct Terrain : public BFObject {

  Terrain( TerrainFeature type, float_t width, float_t height );
  virtual ~Terrain() = default;

  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  ////////////////////////////////////////////////

  float_t width() override;

  float_t height() override;

  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  ////////////////////////////////////////////////

  TerrainFeature                    m_feature;    ///< The feature type of the terrain
  float_t                           m_width;      ///< The width of the terrain
  float_t                           m_height;     ///< The height of the terrain
};


} /* tnasdk */ 
#endif /* _TNASDK_TERRAIN_H_ */


