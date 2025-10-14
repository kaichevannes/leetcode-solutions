cmake_minimum_required(VERSION 3.28)
project("interview-150")

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler warnings
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

# Enable RapidCheck GTest support
set(RC_ENABLE_GTEST ON CACHE BOOL "Enable GTest support for RapidCheck")

FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(rapidcheck)

# Testing
enable_testing()

add_subdirectory(001-merge-sorted-array)
