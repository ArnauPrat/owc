

#include <unit.h>
#include <physical_factory.h>
#include <tnasdk.h>

namespace tnasdk {

Unit::Unit ( TroopType troop_type,
             uint8_t num_ranks, 
             uint8_t num_files,
             uint8_t troop_width,
             uint8_t troop_height) {
  p_punit = pfactory->create_punit( num_ranks, num_files );
}

Unit::~Unit () {
}
  
} /* tnasdk */ 
