add_executable(sine_test sine_test.cpp)

target_link_libraries(sine_test PRIVATE IBDSP)

# Register the test with CTest
add_test(NAME sine_test COMMAND sine_test)
