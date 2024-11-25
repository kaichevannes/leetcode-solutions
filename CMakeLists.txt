cmake_minimum_required(VERSION 3.28)
project("interview-150")

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Config
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include
include_directories(${PROJECT_SOURCE_DIR}/src)

# Enable RapidCheck GTest support
set(RC_ENABLE_GTEST ON CACHE BOOL "Enable GTest support for RapidCheck")

# Third party libraries
add_subdirectory(third_party/gtest)
add_subdirectory(third_party/rapidcheck)

# Testing
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
