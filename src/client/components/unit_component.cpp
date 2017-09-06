


#include "unit_component.h"

namespace owc {

UnitComponent::UnitComponent( tnasdk::TroopType troop_type, 
                              uint32_t num_files, 
                              uint32_t num_ranks,
                              float  troop_width,
                              float  troop_height
                            ) {

  p_unit = tnasdk::create_unit(troop_type, 
                               num_files, 
                               num_ranks, 
                               troop_width, 
                               troop_height);
}

UnitComponent::~UnitComponent() {
  tnasdk::destroy_unit(p_unit);
}
  
} /* owc */ 
