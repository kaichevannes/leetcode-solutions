cmake_minimum_required(VERSION 3.28)
project("leetcode")

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
FetchContent_Declare(
  rapidcheck
  GIT_REPOSITORY  https://github.com/emil-e/rapidcheck
  GIT_TAG ff6af6fc683159deb51c543b065eba14dfcf329b
)

set(RC_ENABLE_GTEST ON CACHE BOOL "Enable GTest support for RapidCheck")

FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(rapidcheck)

enable_testing()

file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "[0-9][0-9][0-9][0-9]_*")
foreach(subdir ${SUBDIRS})
    if(NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}")
      message(FATAL_ERROR "Expected ${subdir} to be a directory")
    endif()

    set(SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/solution.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/test.cc"
    )

    add_executable(${subdir} ${SRC_FILES})
    target_link_libraries(${subdir} PRIVATE gtest gtest_main rapidcheck rapidcheck_gtest)

    include(GoogleTest)
    gtest_discover_tests(${subdir})
endforeach()
