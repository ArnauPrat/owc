
#ifndef _FURIOUS_DATA_COMMON_H_
#define _FURIOUS_DATA_COMMON_H_

#include "../common/types.h"

namespace furious {
namespace data {

using EntityId = uint32_t;
using TableId  = uint32_t;
using SystemId = uint32_t;

constexpr TableId INVALID_ID = 0xffffffff;

} /* data */ 
} /* furious */ 

#endif
