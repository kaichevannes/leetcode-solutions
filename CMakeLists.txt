cmake_minimum_required(VERSION 3.28)
project("interview-150")

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(GoogleTest)

gtest_add_tests(tests)
