
#ifndef _OWC_RECT_COMPONENT_H_
#define _OWC_RECT_COMPONENT_H_ value

#include "../utils.h"
#include <cstdint>
#include <tnasdk/tnasdk.h>


namespace owc {

struct RectComponent {
  COMPONENT(RectComponent);

  RectComponent();

  virtual ~RectComponent();

};
  
} /* owc */ 

#endif /* ifndef _OWC_UNIT_COMPONENT_H_ */
