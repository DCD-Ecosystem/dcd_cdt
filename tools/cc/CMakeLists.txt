configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dcd-cc.cpp.in ${CMAKE_BINARY_DIR}/dcd-cc.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dcd-cpp.cpp.in ${CMAKE_BINARY_DIR}/dcd-cpp.cpp)

add_tool(dcd-cc)
add_tool(dcd-cpp)

set_target_properties(dcd-cc PROPERTIES LINK_FLAGS "-Wl,-rpath,\"\\$ORIGIN/../lib\"")
set_target_properties(dcd-cpp PROPERTIES LINK_FLAGS "-Wl,-rpath,\"\\$ORIGIN/../lib\"")
