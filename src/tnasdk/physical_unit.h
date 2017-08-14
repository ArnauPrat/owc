

#ifndef _TNASDK_PHYSICAL_UNIT_H_
#define _TNASDK_PHYSICAL_UNIT_H_

#include <common.h>
#include <vector>

namespace tnasdk {

/**
 * @brief Interface representing the physical component of a unit (i.e. its
 * position, space, etc.)
 */
class PhysicalUnit {
public:
  PhysicalUnit() = delete;
  PhysicalUnit( uint8_t num_ranks, 
                uint8_t num_files,
                uint8_t troop_width,
                uint8_t troop_height
                );

  virtual ~PhysicalUnit() = default;

  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  
  /**
   * @brief Sets the position of the physical unit
   *
   * @param position The position 
   */
  virtual void position( Vector2f position ) = 0;

  /**
   * @brief Gets the position of the physical unit
   *
   * @return  The position of the physical unit
   */
  virtual Vector2f position() const = 0;

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
  
private:
  uint8_t     m_num_ranks;
  uint8_t     m_num_files;
  uint8_t     m_troop_width;
  uint8_t     m_troop_height;
  std::vector<bool_t> m_toop_mask; // a vector of size num_ranks x num_files
};

} /* tnasdk */ 
#endif /* _TNASDK_PHYSICAL_UNIT_H_ */
