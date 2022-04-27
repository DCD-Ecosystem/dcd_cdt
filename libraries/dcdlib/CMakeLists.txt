file(GLOB HEADERS "*.hpp"
                  "*.h")

add_library(dcd
            dcdlib.cpp
            crypto.cpp
            ${HEADERS})

add_library(dcd_malloc
            malloc.cpp
            ${HEADERS})

add_library(dcd_dsm
            simple_malloc.cpp
            ${HEADERS})

add_library(dcd_cmem
            memory.cpp
            ${HEADERS})


set_target_properties(dcd_malloc PROPERTIES LINKER_LANGUAGE C)

target_include_directories(dcd PUBLIC
                                 ${CMAKE_SOURCE_DIR}/libc/musl/include
                                 ${CMAKE_SOURCE_DIR}/libc/musl/src/internal
                                 ${CMAKE_SOURCE_DIR}/libc/musl/src/crypt
                                 ${CMAKE_SOURCE_DIR}/libc/musl/arch/dcd
                                 ${CMAKE_SOURCE_DIR}/libcxx/include
                                 ${CMAKE_SOURCE_DIR}
                                 ${CMAKE_SOURCE_DIR}/boost/include)

target_link_libraries( dcd c c++ )
add_custom_command( TARGET dcd POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:dcd> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET dcd_malloc POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:dcd_malloc> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET dcd_dsm POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:dcd_dsm> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET dcd_cmem POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:dcd_cmem> ${BASE_BINARY_DIR}/lib )

if (ENABLE_NATIVE_COMPILER)
   add_native_library(native_dcd
                      dcdlib.cpp
                      crypto.cpp
                      malloc.cpp
                      ${HEADERS})

   add_dependencies( native_dcd dcd )
   add_custom_command( TARGET native_dcd POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:native_dcd> ${BASE_BINARY_DIR}/lib )
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../dcdlib DESTINATION ${BASE_BINARY_DIR}/include FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
