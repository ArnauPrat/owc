


#ifndef TNASDK_UNIT_H_
#define TNASDK_UNIT_H_
#include <common.h>

namespace tnasdk {

class PhysicalUnit;

/**
 * @brief A unit of The Ninth Age. 
 */
class Unit {
public:
  Unit ( TroopType troop_type,
         uint8_t num_ranks, 
         uint8_t num_files,
         uint8_t troop_width,
         uint8_t troop_height);
  virtual ~Unit ();

  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  ////////////////////////////////////////////////


private:
  TroopType     m_troop_type;
  PhysicalUnit* p_punit;

};
} /* tnasdk */ 

#endif /* UNIT_H */


