


#ifndef _OWC_UNIT_COMPONENT_H_
#define _OWC_UNIT_COMPONENT_H_ value

#include "../utils.h"
#include <cstdint>
#include <tnasdk/tnasdk.h>


namespace owc {

struct UnitComponent {
  COMPONENT(UnitComponent);

  UnitComponent( tnasdk::TroopType troop_type, 
                 uint32_t num_files, 
                 uint32_t num_ranks,
                 float  troop_width,
                 float  troop_height
                 );

  virtual ~UnitComponent();


  tnasdk::Unit*   p_unit;

};
  
} /* owc */ 

#endif /* ifndef _OWC_UNIT_COMPONENT_H_ */
