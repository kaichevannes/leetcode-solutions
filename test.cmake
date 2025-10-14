# CommonTest.cmake
get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_executable(${TARGET_NAME} solution.cc test.cc)
target_link_libraries(${TARGET_NAME} PRIVATE gtest gtest_main rapidcheck rapidcheck_gtest)
include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})
