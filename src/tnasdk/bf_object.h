

#ifndef _TNASDK_BFOBJECT_H_
#define _TNASDK_BFOBJECT_H_

#include <string>

namespace tnasdk {

struct BFObject {
  BFObject( const std::string& type );
  virtual ~BFObject() = default;
  const std::string m_type; ///< The type of the object
};
  
} /* tnasdk */ 

#endif /* ifndef _TNASDK_BFOBJECT_H_ */
