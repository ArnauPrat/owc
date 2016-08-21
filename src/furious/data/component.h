

#ifndef _FURIOUS_COMPONENT_H_
#define _FURIOUS_COMPONENT_H_

#include <common/platform.h>
#include <data/datatypes.h>
#include <string>
#include <vector>

namespace furious {
  namespace data {

    struct Field {
      std::string m_name;
      DataType    m_type;
      uint_t      m_stride;
    };

    class ComponentType;

    class ComponentIterator {

      public:
        bool HasNext();
        Component Next();

      private:
        friend class ComponentType;
        ComponentIteartor(ComponentType* );

        ComponentCollection*  m_componentType;

    };

    class ComponentType {

      private:
        uint_t              m_componentTypeId;
        std::vector<uint_t> m_entityIds;
        std::vector<Field>  m_fields;
        char_t*             m_data;
    };
  }
}

#endif
