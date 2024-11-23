include(test_files.cmake)

list(APPEND TEST_FILES
  ${ARRAY_STRING_TEST_FILES}
  ${HASHMAP_TEST_FILES}
  ${MATRIX_TEST_FILES}
  ${SLIDING_WINDOW_TEST_FILES}
  ${TWO_POINTERS_TEST_FILES}
  ${INTERVALS_TEST_FILES}
  ${STACK_TEST_FILES}
)

foreach(TEST_FILE ${TEST_FILES})
  get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

  add_executable(${TEST_NAME} ${TEST_FILE})

  target_link_libraries(${TEST_NAME} PRIVATE gtest gtest_main InterviewQuestions rapidcheck rapidcheck_gtest)
  
  include(GoogleTest)

  gtest_discover_tests(${TEST_NAME})
endforeach()
