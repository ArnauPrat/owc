
add_definitions(${FURIOUS_DEFAULT_DEFINES})
include_directories(${FURIOUS_INCLUDE_DIR})

#add_subdirectory(code_generator)

add_library(data STATIC
  common.h
  database.h
  database.cpp
  execution_engine.cpp
  execution_engine.h
  logic_filter.h
  logic_filter.cpp
  logic_join.h
  logic_join.cpp
  logic_map.h
  logic_map.cpp
  logic_plan.h
  logic_scan.h
  logic_scan.cpp
  logic_plan_visitor.h
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
