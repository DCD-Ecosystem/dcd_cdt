configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dcd-abidiff.cpp.in ${CMAKE_BINARY_DIR}/dcd-abidiff.cpp)

add_tool(dcd-abidiff)

set_target_properties(dcd-abidiff PROPERTIES LINK_FLAGS "-Wl,-rpath,\"\\$ORIGIN/../lib\"")
