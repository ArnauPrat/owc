
add_definitions(${FURIOUS_DEFAULT_DEFINES})
include_directories(${FURIOUS_INCLUDE_DIR})

add_library(common STATIC
  platform.cpp
)

target_link_libraries(common)
