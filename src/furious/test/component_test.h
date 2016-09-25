


#include <gtest/gtest.h>
#include <common/types.h>
#include <data/component.h>

namespace furious {
  namespace data {
    class ComponentTest : public ::testing::Test {
      protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }

    };

    COMPONENT_IDENTIFIER(field_char_t);
    COMPONENT_IDENTIFIER(field_int8_t);
    COMPONENT_IDENTIFIER(field_int16_t);
    COMPONENT_IDENTIFIER(field_int32_t);
    COMPONENT_IDENTIFIER(field_int64_t);
    COMPONENT_IDENTIFIER(field_uint8_t);
    COMPONENT_IDENTIFIER(field_uint16_t);
    COMPONENT_IDENTIFIER(field_uint32_t);
    COMPONENT_IDENTIFIER(field_uint64_t);
    COMPONENT_IDENTIFIER(field_float_t);
    COMPONENT_IDENTIFIER(field_double_t);

    TEST_F(ComponentTest,ComponentWorks) {
      Component<field_char_t<char_t>, 
        field_int8_t<int8_t>,
        field_int16_t<int16_t>,
        field_int32_t<int32_t>,   
        field_int64_t<int64_t>,
        field_uint8_t<uint8_t>,
        field_uint16_t<uint16_t>,
        field_uint32_t<uint32_t>,
        field_uint64_t<uint64_t>,
        field_float_t<float_t>,
        field_double_t<double_t>> component = { '\0',
                                                  0,
                                                  0,
                                                  0,
                                                  0L,
                                                  0,
                                                  0,
                                                  0,
                                                  0L,
                                                  0.0f,
                                                  0.0
                                                };

        ASSERT_TRUE(component.field_char_t == '\0');
        ASSERT_TRUE(component.field_int8_t == 0);
        ASSERT_TRUE(component.field_int16_t == 0);
        ASSERT_TRUE(component.field_int32_t == 0);
        ASSERT_TRUE(component.field_int64_t == 0L);
        ASSERT_TRUE(component.field_uint8_t == 0);
        ASSERT_TRUE(component.field_uint16_t == 0);
        ASSERT_TRUE(component.field_uint32_t == 0);
        ASSERT_TRUE(component.field_uint64_t == 0L);
        ASSERT_TRUE(component.field_float_t == 0.0f);
        ASSERT_TRUE(component.field_double_t == 0.0);

        ASSERT_TRUE(component.size_of<field_char_t<char_t>>() == sizeof(char_t));
        ASSERT_TRUE(component.size_of<field_int8_t<int8_t>>() == sizeof(int8_t));
        ASSERT_TRUE(component.size_of<field_int16_t<int16_t>>() == sizeof(int16_t));
        ASSERT_TRUE(component.size_of<field_int32_t<int32_t>>() == sizeof(int32_t));
        ASSERT_TRUE(component.size_of<field_int64_t<int64_t>>() == sizeof(int64_t));
        ASSERT_TRUE(component.size_of<field_uint8_t<uint8_t>>() == sizeof(uint8_t));
        ASSERT_TRUE(component.size_of<field_uint16_t<uint16_t>>() == sizeof(uint16_t));
        ASSERT_TRUE(component.size_of<field_uint32_t<uint32_t>>() == sizeof(uint32_t));
        ASSERT_TRUE(component.size_of<field_uint64_t<uint64_t>>() == sizeof(uint64_t));
        ASSERT_TRUE(component.size_of<field_float_t<float_t>>() == sizeof(float_t));
        ASSERT_TRUE(component.size_of<field_double_t<double_t>>() == sizeof(double_t));
      }
  }
}

