CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT( furious )

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -O0 -g -pg ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g -pg -DNDEBUG -ftree-vectorize -ftree-vectorizer-verbose=7 -fopt-info-vec-all")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g -pg -DNDEBUG")

set(FURIOUS_DEFAULT_DEFINES " ")
set(FURIOUS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(FURIOUS_OUTPUT_DIR "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/furious")

include_directories(./)

add_subdirectory(./common/)
add_subdirectory(./memory/)
add_subdirectory(./data/)
add_subdirectory(./runtime/)

add_library(furious SHARED
  furious.h
  furious.cpp
  furious.inl
  )  

target_link_libraries(furious common memory data runtime)

set_target_properties(furious 
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${FURIOUS_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${FURIOUS_OUTPUT_DIR}
  ARCHIVE_OUTPUT_DIRECTORY ${FURIOUS_OUTPUT_DIR}
)


add_executable( furious_test 
  furious_test.cpp
  )
target_link_libraries( furious_test furious )

set_target_properties(furious_test
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${FURIOUS_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${FURIOUS_OUTPUT_DIR}
  ARCHIVE_OUTPUT_DIRECTORY ${FURIOUS_OUTPUT_DIR}
)


add_subdirectory(./test/)

SET(FURIOUS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

