configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dcd-init.cpp ${CMAKE_BINARY_DIR}/dcd-init.cpp @ONLY)

add_tool(dcd-init)

set_target_properties(dcd-init PROPERTIES LINK_FLAGS "-Wl,-rpath,\"\\$ORIGIN/../lib\"")
