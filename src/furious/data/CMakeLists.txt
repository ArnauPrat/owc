
add_definitions(${FURIOUS_DEFAULT_DEFINES})
include_directories(${FURIOUS_INCLUDE_DIR})

add_library(data STATIC
  btree.h
  btree.inl
  common.h
  database.inl
  database.cpp
  database.h
  impl/btree_impl.cpp
  impl/btree_impl.h
  table.h
  table.cpp
)

target_link_libraries(data common memory)

set_target_properties( data 
 PROPERTIES
 LIBRARY_OUTPUT_DIRECTORY ${FURIOUS_OUTPUT_DIR}
 ARCHIVE_OUTPUT_DIRECTORY ${FURIOUS_OUTPUT_DIR}
)
