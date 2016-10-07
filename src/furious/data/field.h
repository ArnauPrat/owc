

#ifndef _FURIOUS_FIELD_H_
#define _FURIOUS_FIELD_H_

#include <utility>
#include <string>

namespace furious
{
  namespace data
  {

    /** Represents a data type in the database. **/
    enum class FIELD_TYPE {
      BOOL,         // Boolean 
      INTEGER,      // 32-bit integer
      LONG,         // 64-bit integer
      STRING,       // Fixed-length string
      FLOAT,        // 32-bit floating point
      DOUBLE,       // 64-bit floating point
      VOID,         // void pointer
    };

    struct FieldInfo {
      uint32_t    offset_;    // The offset of the field within the structure
      size_t      size_;      // The size in bytes of the field 
      FIELD_TYPE  type_;      // The type of the field 
      std::string name_;      // The name of the field

      /**
       * Copy constructor
       */
      FieldInfo( uint32_t offset, size_t size, FIELD_TYPE type, const std::string & name ) :
        offset_(offset), size_(size), type_(type), name_(name) {

        }

      /**
       * Move constructor
       */
      FieldInfo( uint32_t offset, size_t size, FIELD_TYPE type, std::string && name ) :
        offset_(offset), size_(size), type_(type), name_(std::forward<std::string>(name)) {

        }
    };
    
  } /* data */ 
  
} /* furiousj */ 



#endif
