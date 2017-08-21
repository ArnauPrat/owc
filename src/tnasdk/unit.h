
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
  
  const TroopType     m_troop_type;
  int32_t             m_num_ranks;
  int32_t             m_num_files;
  float_t             m_troop_width;
  float_t             m_troop_height;
  std::vector<bool_t> m_troop_mask; // a vector of size num_ranks x num_files
  BBox*               p_bbox;
};
} /* tnasdk */ 

#endif /* _TNASDK_UNIT_H_ */


