project(singleton_example)

set(DCD_WASM_OLD_BEHAVIOR "Off")
find_package(dcd.cdt)

add_contract( singleton_example singleton_example singleton_example.cpp )
target_include_directories( singleton_example PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( singleton_example ${CMAKE_SOURCE_DIR}/../ricardian )