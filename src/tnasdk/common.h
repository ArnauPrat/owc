

#ifndef _TNASDK_TYPES_H
#define _TNASDK_TYPES_H 


namespace tnasdk {

#define INCHES_TO_CMS 2.54f
#define INCHES_TO_MMS 25.4f
#define MMS_TO_INCHES 0.0394
#define CMS_TO_INCHES 0.394

#define PI 3.14159265359f
#define DEGREES_TO_RADS PI/180.0f
#define RADS_TO_DEGREES 180.0f/PI

enum class Footprint {
  E_HALF,
  E_FULL,
  E_OUT
};
} /* tnasdk */ 

#include <types.h>
#include <troop_type.h>
#include <vector.h>

#endif /* ifndef _TNASDK_TYPES_H */


