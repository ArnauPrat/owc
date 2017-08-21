

#ifndef _TNASDK_BBOX_H_
#define _TNASDK_BBOX_H_

#include <common.h>
#include <transform.h>

namespace tnasdk {

/**
 * @brief Interface representing a bounding box of a battlefield element (i.e. its
 * position, space, etc.)
 */
class BBox {
public:
  BBox() = default;
  virtual ~BBox() = default;

  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  

  /**
   * @brief Sets the transform of this physical unit
   *
   * @param transform The tranform to set
   *
   * @return Returns true if bbox collides with something
   */
  virtual bool_t transform(Transform transform) = 0;

  /**
   * @brief Gets the transform of this physical unit
   *
   * @return Returns the current transform of this physical unit
   */
  virtual Transform transform() const = 0;


  /**
   * @brief Sets the position of the bounding box
   *
   * @param position The position to set
   */
  virtual void position( Vector2f position ) = 0;

  /**
   * @brief Gets the position of the bounding box
   *
   * @return The position of the bounding box
   */
  virtual Vector2f position() const = 0;
  
  /**
   * @brief Sets the rotation of the bounding box
   *
   * @param angle The angle of the rotation to set
   */
  virtual void rotation( float_t angle )  = 0;

  /**
   * @brief Gets the rotation of the bounding box
   *
   * @return  Returns the angle of the rotation
   */
  virtual float_t rotation() const = 0;

  /**
   * @brief Sets the width of the physical unit
   *
   * @param width The width of the physical unit
   */
  virtual void width( float_t width ) = 0;

  /**
   * @brief Gets the width of the physical unit
   *
   * @return  The width of the physical unit
   */
  virtual float_t width() = 0;

  /**
   * @brief Sets the height of the physical unit
   *
   * @param height The height of the physical unit
   */
  virtual void height( float_t height ) = 0;

  /**
   * @brief Gets the height of the physical unit
   *
   * @return  The height of the physical unit
   */
  virtual float_t height() = 0;


  /**
   * @brief Enables the bounding box and makes it to influence the collisions
   */
  virtual void enable() = 0;

  /**
   * @brief Disables the bounding box and makes it not to influence the
   * collisions
   */
  virtual void disable() = 0;
};

} /* tnasdk */ 
#endif /* _TNASDK_UNIT_BBOX_H_ */
