CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT( furious_tests )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -O0 -g -pg ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG ")

add_definitions(${FURIOUS_DEFAULT_DEFINES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${FURIOUS_INCLUDE_DIR})

add_executable(furious_test
  furious_test.cpp
  )

target_link_libraries(furious_test ${GTEST_LIBRARIES} furious)

add_test(furious_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/furious_test)


