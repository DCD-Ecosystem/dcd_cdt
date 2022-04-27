project(multi_index_large)

set(DCD_WASM_OLD_BEHAVIOR "Off")
find_package(dcd.cdt)

add_contract( multi_index_large multi_index_large multi_index_large.cpp )
target_include_directories( multi_index_large PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( multi_index_large ${CMAKE_SOURCE_DIR}/../ricardian )
