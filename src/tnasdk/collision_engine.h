

#ifndef _TNASDK_COLLISION_ENGINE_H_
#define _TNASDK_COLLISION_ENGINE_H_

#include <common.h>
#include <transform.h>

namespace tnasdk {

class BBox;

/**
 * @brief Interface of a factory in charge of creating PhysicalUnits
 */
class CollisionEngine {
public:
  CollisionEngine () = default;
  virtual ~CollisionEngine () = default;

  /**
   * @brief Creates a bounding box at origin, size 1.0f and rotation 0.0f. The
   * bbox is disabled by default 
   *
   * @return Returns a newly created bounding box
   */
  virtual BBox* create_bbox() = 0;

  /**
   * @brief Destroys a bounding box 
   *
   * @param punit A pointer to the bounding box willing to destroy
   */
  virtual void destroy_bbox( BBox* bbox ) = 0;
};

} /* tnasdk */ 
#endif /* _TNASDK_PHYSICAL_FACTORY_H_ */
