
#ifndef _FURIOUS_RUNTIME_COMMON_H_
#define _FURIOUS_RUNTIME_COMMON_H_

#include "../common/types.h"

namespace furious {

using EntityId = uint32_t;
using TableId  = uint32_t;
using SystemId = uint32_t;

constexpr TableId INVALID_ID = 0xffffffff;

} /* furious */ 

#endif
