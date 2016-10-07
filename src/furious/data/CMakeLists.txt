
add_definitions(${FURIOUS_DEFAULT_DEFINES})
include_directories(${FURIOUS_INCLUDE_DIR})

add_library(data STATIC
  component.h
  database.cpp
  database.h
  field.h
  irow.h
  isystem.h
  itable.h
  itable_iterator.h
  system.h
  table.h
)

target_link_libraries(data)
