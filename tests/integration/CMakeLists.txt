cmake_minimum_required( VERSION 3.5 )

set(DCD_VERSION_MIN "2.0")
set(DCD_VERSION_SOFT_MAX "3.0")
#set(DCD_VERSION_HARD_MAX "")

find_package(dcd)

### Check the version of dcd
set(VERSION_MATCH_ERROR_MSG "")
DCD_CHECK_VERSION(VERSION_OUTPUT "${DCD_VERSION}"
                                   "${DCD_VERSION_MIN}"
                                   "${DCD_VERSION_SOFT_MAX}"
                                   "${DCD_VERSION_HARD_MAX}"
                                   VERSION_MATCH_ERROR_MSG)
if(VERSION_OUTPUT STREQUAL "MATCH")
   message(STATUS "Using dcd version ${DCD_VERSION}")
elseif(VERSION_OUTPUT STREQUAL "WARN")
   message(WARNING "Using dcd version ${DCD_VERSION} even though it exceeds the maximum supported version of ${DCD_VERSION_SOFT_MAX}; continuing with configuration, however build may fail.\nIt is recommended to use dcd version ${DCD_VERSION_SOFT_MAX}.x")
else() # INVALID OR MISMATCH
   message(FATAL_ERROR "Found dcd version ${DCD_VERSION} but it does not satisfy version requirements: ${VERSION_MATCH_ERROR_MSG}\nPlease use dcd version ${DCD_VERSION_SOFT_MAX}.x")
endif(VERSION_OUTPUT STREQUAL "MATCH")


enable_testing()

configure_file(${CMAKE_SOURCE_DIR}/contracts.hpp.in ${CMAKE_BINARY_DIR}/contracts.hpp)

include_directories(${CMAKE_BINARY_DIR})

file(GLOB INT_TESTS "*.cpp" "*.hpp")

add_dcd_test_executable( integration_tests ${INT_TESTS} )

foreach(TEST_SUITE ${INT_TESTS}) # create an independent target for each test suite
  execute_process(COMMAND bash -c "grep -E 'BOOST_AUTO_TEST_SUITE\\s*[(]' ${TEST_SUITE} | grep -vE '//.*BOOST_AUTO_TEST_SUITE\\s*[(]' | cut -d ')' -f 1 | cut -d '(' -f 2" OUTPUT_VARIABLE SUITE_NAME OUTPUT_STRIP_TRAILING_WHITESPACE) # get the test suite name from the *.cpp file
  if (NOT "" STREQUAL "${SUITE_NAME}") # ignore empty lines
    execute_process(COMMAND bash -c "echo ${SUITE_NAME} | sed -e 's/s$//' | sed -e 's/_test$//'" OUTPUT_VARIABLE TRIMMED_SUITE_NAME OUTPUT_STRIP_TRAILING_WHITESPACE) # trim "_test" or "_tests" from the end of ${SUITE_NAME}
    # to run unit_test with all log from blockchain displayed, put "--verbose" after "--", i.e. "unit_test -- --verbose"
    add_test(NAME ${TRIMMED_SUITE_NAME}_integration_test COMMAND integration_tests --run_test=${SUITE_NAME} --report_level=detailed --color_output)
    # build list of tests to run during coverage testing
    if(ctest_tests)
        string(APPEND ctest_tests "|")
    endif()
    string(APPEND ctest_tests ${TRIMMED_SUITE_NAME}_integration_test)
  endif()
endforeach(TEST_SUITE)
set(ctest_tests "'${ctest_tests}' -j8") # surround test list string in apostrophies
