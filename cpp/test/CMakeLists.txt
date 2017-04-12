set(TEST_FILES main_test.cpp math_test.cpp)

add_executable(${PROJECT_NAME}_tests ${TEST_FILES})
#target_link_libraries(${PROJECT_NAME}_tests ${PROJECT_NAME})