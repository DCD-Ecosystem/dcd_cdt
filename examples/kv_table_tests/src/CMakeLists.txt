project(kvtest)

set(DCD_WASM_OLD_BEHAVIOR "Off")
find_package(dcd.cdt)

add_contract( kvtest kvtest kvtest.cpp )
target_ricardian_directory( kvtest ${CMAKE_SOURCE_DIR}/../ricardian )