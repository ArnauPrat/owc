CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT( tnasdk )

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -O0 -g -pg ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG ")

set(TNASDK_DEFAULT_DEFINES " ")
set(TNASDK_INCLUDE_DIR ${CMAKE_SOURCE_DIR})
set(TNASDK_OUTPUT_DIR "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/tnasdk")

include_directories(./)

add_library(tnasdk STATIC
  common.h
  physical_factory.h
  physical_unit.cpp
  physical_unit.h
  tnasdk.cpp
  tnasdk.h
  troop_type.cpp
  troop_type.h
  types.h
  unit.cpp
  unit.h
  )  

set_target_properties(furious 
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${TNASDK_OUTPUT_DIR}
  ARCHIVE_OUTPUT_DIRECTORY ${TNASDK_OUTPUT_DIR}
)
