configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dcd-ld.cpp.in ${CMAKE_BINARY_DIR}/dcd-ld.cpp)

add_tool(dcd-ld)

set_target_properties(dcd-ld PROPERTIES LINK_FLAGS "-Wl,-rpath,\"\\$ORIGIN/../lib\"")
