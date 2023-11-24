set(SRC_FILES gtest_validation.cpp)

################################
# Unit Test Files
################################
add_executable(${PROJECT_NAME}_test ${SRC_FILES})

# Link test executable against gtest & gtest_main
target_link_libraries(${PROJECT_NAME}_test gtest gtest_main)


######################################
# Configure the test to use GoogleTest
#
# If used often, could be made a macro.
enable_testing()
add_test(NAME    ${PROJECT_NAME}_test
         COMMAND ${PROJECT_NAME}_test)
