
add_definitions(${FURIOUS_DEFAULT_DEFINES})
include_directories(${FURIOUS_INCLUDE_DIR})

add_library(data STATIC
  database.h
  isystem.h
  itable.h
  itable_iterator.h
  system.h
  table.h
  execution_engine.h
  execution_engine.cpp
)

target_link_libraries(data)
