

#ifndef _TNASDK_COLLISION_ENGINE_H_
#define _TNASDK_COLLISION_ENGINE_H_

#include "common.h"
#include "transform.h"
#include "vector"

namespace tnasdk {

class BBox;
class BFObject;

struct Collision {
  const BBox* p_bbox_a;
  const BBox* p_bbox_b;
};

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
   * @param user_data A void pointer with the user data to associate with the
   * bbox
   *
   * @return Returns a newly created bounding box
   */
  virtual BBox* create_bbox( BFObject* user_data ) = 0;

  /**
   * @brief Destroys a bounding box 
   *
   * @param punit A pointer to the bounding box willing to destroy
   */
  virtual void destroy_bbox( BBox* bbox ) = 0;


  /**
   * @brief Detexts the collisions between BBoxes
   *
   * @return Returns a vector with the collisions information
   */
  virtual std::vector<Collision> detect_collisions() = 0;


  /**
   * @brief Gets the bboxes created
   *
   * @return Returns a vector with the bboxes created
   */
  virtual std::vector<BBox*>  bboxes() = 0;

};

} /* tnasdk */ 
#endif /* _TNASDK_PHYSICAL_FACTORY_H_ */
