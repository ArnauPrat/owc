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
set(TNASDK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TNASDK_OUTPUT_DIR "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/tnasdk")

MESSAGE(STATUS "TNASDK INCLUDE DIR: ${TNASDK_INCLUDE_DIR}")

add_subdirectory(./bullet)

include_directories(./)

add_library(tnasdk STATIC
  common.h
  movement.h
  collision_engine.h
  bbox.h
  terrain.h
  terrain.cpp
  tnasdk.cpp
  tnasdk.h
  troop_type.cpp
  troop_type.h
  types.h
  unit.cpp
  unit.h
  vector.h
)  

target_link_libraries(tnasdk tnabullet ${TNABULLET_LIBRARIES})

set_target_properties(tnasdk
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${TNASDK_OUTPUT_DIR}
  ARCHIVE_OUTPUT_DIRECTORY ${TNASDK_OUTPUT_DIR}
)

SET(TNASDK_LIBRARIES 
  tnasdk 
  ${TNABULLET_LIBRARIES})

SET(TNASDK_LIBRARIES 
  tnasdk 
  ${TNABULLET_LIBRARIES}
  PARENT_SCOPE)

SET(TNASDK_LIBRARY_DIR 
  ${TNABULLET_LIBRARY_DIR})

SET(TNASDK_LIBRARY_DIR 
  ${TNABULLET_LIBRARY_DIR}
  PARENT_SCOPE)

add_subdirectory(./test)
