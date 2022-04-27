include(ExternalProject)
# if no cdt root is given use default path
if(DCD_CDT_ROOT STREQUAL "" OR NOT DCD_CDT_ROOT)
   find_package(dcd.cdt)
endif()

ExternalProject_Add(
   kv_addr_book_project
   SOURCE_DIR ${CMAKE_SOURCE_DIR}/src
   BINARY_DIR ${CMAKE_BINARY_DIR}/kv_addr_book
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${DCD_CDT_ROOT}/lib/cmake/dcd.cdt/DcdWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)