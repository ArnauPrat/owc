

#ifndef _TNASDK_BFOBJECT_H_
#define _TNASDK_BFOBJECT_H_

#include <common.h>
#include <string>
#include <bbox.h>
#include <vector.h>

namespace tnasdk {

struct BFObject {
  BFObject( const std::string& type );
  virtual ~BFObject() = default;

  /**
   * @brief Gets the position of the object
   *
   * @return Returns the position of the uni
   */
  virtual Vector2f position();

  /**
   * @brief Sets the position of the object
   *
   * @param position The position to set
   */
  virtual void  position( Vector2f position );

  /**
   * @brief Gets the rotation of the object
   *
   * @return Returns the rotation of the object
   */
  virtual float_t rotation();

  /**
   * @brief Sets the rotation of the object
   *
   * @param rotation The rotation to set
   */
  virtual void rotation( float_t rotation );

  /**
   * @brief Gets the width of the battlefield object
   *
   * @return  Returns the width of the battlefield object
   */
  virtual float_t width() = 0;

  /**
   * @brief Gets the height of the battlefield object
   *
   * @return  Returns the height of the battlefield object
   */
  virtual float_t height() = 0;

  const std::string m_type;   ///< The type of the object
  BBox*             p_bbox;
};
  
} /* tnasdk */ 

#endif /* ifndef _TNASDK_BFOBJECT_H_ */
