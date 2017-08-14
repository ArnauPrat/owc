

#include <tnasdk.h>
#include <common.h>
#include <physical_factory.h>
#include <unit.h>

namespace tnasdk {

PhysicalFactory* pfactory = nullptr;

void init_tnasdk( PhysicalFactory* pfactory ) {
  tnasdk::pfactory = pfactory;
}

Unit* create_unit(TroopType troop_type,
                  uint8_t num_ranks, 
                  uint8_t num_files,
                  uint8_t troop_width,
                  uint8_t troop_height) {

  return new Unit(troop_type, 
                  num_ranks,
                  num_files,
                  troop_width,
                  troop_height);
}

void destroy_unit(Unit* unit) {
  delete unit;
}
  
} /* tnask */ 
