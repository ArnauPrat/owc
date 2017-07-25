
add_definitions(${FURIOUS_DEFAULT_DEFINES})
include_directories(${FURIOUS_INCLUDE_DIR})

#add_subdirectory(code_generator)

add_library(data STATIC
  common.h
  database.h
  execution_engine.cpp
  execution_engine.h
  logic_filter.h
  logic_join.h
  logic_map.h
  logic_plan.h
  logic_scan.h
  physical/physical_filter.cpp
  physical/physical_filter.h
  physical/physical_hash_join.cpp
  physical/physical_hash_join.h
  physical/physical_map.cpp
  physical/physical_map.h
  physical/physical_plan.h
  physical/physical_scan.cpp
  physical/physical_scan.h
  physical_plan_generator.cpp
  static_system.h
  static_table.h
  system.h
  table.h
)

target_link_libraries(data)
