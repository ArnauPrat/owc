CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT( tnabullet )

#SET(BULLET_ROOT "/home/aprat/source/bullet3/build_cmake/dist/")
SET(BULLET_ROOT "/usr/")
SET(BULLET_INCLUDE_DIR "${BULLET_ROOT}/include/bullet")
SET(BULLET_LIBRARY_DIR "${BULLET_ROOT}/lib")

SET(BULLET_LIBRARIES
  ${BULLET_LIBRARY_DIR}/libBullet3Common.so
  ${BULLET_LIBRARY_DIR}/libBulletCollision.so
  ${BULLET_LIBRARY_DIR}/libBullet3Collision.so
  ${BULLET_LIBRARY_DIR}/libBulletDynamics.so
  ${BULLET_LIBRARY_DIR}/libBullet3Dynamics.so
  ${BULLET_LIBRARY_DIR}/libBullet3Geometry.so
  ${BULLET_LIBRARY_DIR}/libLinearMath.so
)

include_directories("./")
include_directories(${TNASDK_INCLUDE_DIR})
include_directories(${BULLET_INCLUDE_DIR})

add_library(tnabullet STATIC
  cebullet.h
  cebullet.cpp
  )  

link_directories(${BULLET_LIBRARY_DIR})
target_link_libraries(tnabullet ${BULLET_LIBRARIES})

set_target_properties(tnabullet
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${TNASDK_OUTPUT_DIR}
  ARCHIVE_OUTPUT_DIRECTORY ${TNASDK_OUTPUT_DIR}
)

SET(TNABULLET_INCLUDE_DIR 
  ${BULLET_INCLUDE_DIR})

SET(TNABULLET_LIBRARIES 
  tnabullet 
  ${BULLET_LIBRARIES}
  PARENT_SCOPE)

SET(TNABULLET_LIBRARY_DIR 
  ${BULLET_LIBRARY_DIR}
  PARENT_SCOPE)
