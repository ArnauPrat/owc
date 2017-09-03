
#ifndef _TNASDK_UNIT_H_
#define _TNASDK_UNIT_H_
#include <common.h>
#include <vector>
#include <bf_object.h>

namespace tnasdk {

class BBox;

/**
 * @brief A unit of The Ninth Age. 
 */
struct Unit : public BFObject {
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

  float_t width() override;

  float_t height() override;

  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  ////////////////////////////////////////////////

  const TroopType     m_troop_type;   ///< The troop type
  const int32_t       m_num_ranks;    ///< The number of ranks
  const int32_t       m_num_files;    ///< The number of files
  const float_t       m_troop_width;  ///< The troop type width
  const float_t       m_troop_height; ///< The troop type height

  std::vector<bool_t> m_troop_mask; // a vector of size num_ranks x num_files
};


} /* tnasdk */ 

#endif /* _TNASDK_UNIT_H_ */


