cmake_minimum_required(VERSION 3.28)
project("interview-150")

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Config
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable RapidCheck GTest support
set(RC_ENABLE_GTEST ON CACHE BOOL "Enable GTest support for RapidCheck")

# Third party libraries
add_subdirectory(third_party/gtest)
add_subdirectory(third_party/rapidcheck)

# Testing
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
