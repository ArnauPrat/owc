CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT( furious_tests )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -O0 -g -pg ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG ")

add_definitions(${TNASDK_DEFAULT_DEFINES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${TNASDK_INCLUDE_DIR})

macro(create_test NAME )
  add_executable(${NAME}
    ${NAME}.cpp
   )

 target_link_libraries(${NAME} ${GTEST_LIBRARIES})
 target_link_libraries(${NAME} ${TNASDK_LIBRARIES})

 add_test(${NAME} ${TNASDK_OUTPUT_DIR}/test/${NAME})

    set_target_properties( ${NAME} 
      PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${TNASDK_OUTPUT_DIR}/test
      )
endmacro(create_test)

create_test ("bbox_test")
create_test ("vector_test")
create_test ("battlefield_test")

