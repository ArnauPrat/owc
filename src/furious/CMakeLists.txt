CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT( furious )

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -O0 -g -pg ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG ")

set(FURIOUS_DEFAULT_DEFINES " ")
set(FURIOUS_INCLUDE_DIR ${CMAKE_SOURCE_DIR})
set(FURIOUS_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/furious/")

include_directories(./)

add_subdirectory(./common/)
add_subdirectory(./data/)

add_library(furious SHARED)  
target_link_libraries(furious common data)

set_target_properties( furious 
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${FURIOUS_OUTPUT_DIR}
  )

add_subdirectory(./test/)
