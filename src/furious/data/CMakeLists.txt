
add_definitions(${FURIOUS_DEFAULT_DEFINES})
include_directories(${FURIOUS_INCLUDE_DIR})

add_library(data STATIC
  common.h
  database.h
  execution_engine.cpp
  execution_engine.h
  isystem.h
  itable.h
  itable_iterator.h
  logic_filter.h
  logic_join.h
  logic_map.h
  logic_plan.h
  logic_scan.h
  physical/physical_plan.h
  physical/physical_scan.cpp
  physical/physical_scan.h
  physical/physical_filter.cpp
  physical/physical_filter.h
  physical/physical_hash_join.cpp
  physical/physical_hash_join.h
  system.h
  table.h
)

target_link_libraries(data)
