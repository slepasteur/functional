cmake_minimum_required(VERSION 3.7)
project(cpp CXX)

set(CMAKE_CXX_FLAGS -std=c++1z)

#set(SOURCE_FILES src/math.hpp)
#add_library(cpp ${SOURCE_FILES})

add_subdirectory(test)
enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}_tests)