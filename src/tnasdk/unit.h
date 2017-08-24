
#ifndef _TNASDK_UNIT_H_
#define _TNASDK_UNIT_H_
#include <common.h>
#include <vector>

namespace tnasdk {

class BBox;

/**
 * @brief A unit of The Ninth Age. 
 */
struct Unit {
public:
  Unit() = delete;
  Unit ( TroopType troop_type,
         int32_t num_ranks, 
         int32_t num_files,
         float_t troop_width,
         float_t troop_height);

  virtual ~Unit ();

  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  
  /**
   * @brief Gets the width of the unit in inches
   *
   * @return Returns the width of the unit in inches
   */
  float_t width();

  /**
   * @brief Gets the height of the unit in inches
   *
   * @return Returns the height of the unit in inches
   */
  float_t height();

  
  const TroopType     m_troop_type;
  int32_t             m_num_ranks;
  int32_t             m_num_files;
  float_t             m_troop_width;
  float_t             m_troop_height;
  std::vector<bool_t> m_troop_mask; // a vector of size num_ranks x num_files
  BBox*               p_bbox;
};

/**
 * @brief Attaches a bbox to the unit
 *
 * @param unit The unit to attach the bbox to
 */
void attach_bbox(Unit* unit);

/**
 * @brief Detaches a bbox from the unit
 *
 * @param unit The unit to detach the bbox from
 */
void detach_bbox(Unit* unit);


} /* tnasdk */ 

#endif /* _TNASDK_UNIT_H_ */


