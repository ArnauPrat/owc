


#ifndef _TNASDK_TERRAIN_H_
#define _TNASDK_TERRAIN_H_

#include <common.h>
#include <troop_type.h>
#include <transform.h>
#include <vector>

namespace tnasdk {

class BBox;

////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////


enum class CoverType {
  E_SOFT,
  E_HARD,
  E_NO_COVER
};

struct CoverModifier {
  CoverType m_type;
  Footprint m_footprint;
};

class Terrain {
public:
  Terrain() = delete;
  Terrain( Transform fransform );
  virtual ~Terrain();

  bool_t                      m_obscuring;  // Whether the terrain is obscuring
  bool_t                      m_dangerous;  // Wehther the terrain is dangerous
  std::vector<TroopType>      m_dtroops;    // Troop types affected by dangerous terrain
  std::vector<CoverModifier>  m_cover;      // The type of cover of this terrain
  BBox*                       p_bbox;
};

} /* tnasdk */ 
#endif /* _TNASDK_TERRAIN_H_ */


