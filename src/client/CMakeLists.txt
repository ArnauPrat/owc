CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT( openwarclient )

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-ignored-attributes")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -O0 -g -pg ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG ")

MESSAGE(STATUS "FURIOUS DIR: ${FURIOUS_INCLUDE_DIR}")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${OGRE_INCLUDE_DIRS})

SET(OPENWARCLIENT_SOURCE_FILES 
  main.cpp
  client.cpp
  client.h
  owc.h
  owc.cpp
  components/unit_component.h
  components/unit_component.cpp
  components/rect_component.h
  components/rect_component.cpp
  )

ADD_EXECUTABLE(openwarclient ${OPENWARCLIENT_SOURCE_FILES})  

ADD_DEPENDENCIES(openwarclient furious ${OGRE_DEPENDENCY} tnasdk )

LINK_DIRECTORIES(${TNASDK_LIBRARY_DIR})
TARGET_LINK_LIBRARIES(openwarclient furious ${OGRE_LIBRARIES} ${OIS_LIBRARIES}
  tnasdk libSDL2.so)


set_target_properties(openwarclient 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/client"
   )
