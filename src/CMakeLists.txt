file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(InterviewQuestions STATIC ${SOURCE_FILES})
