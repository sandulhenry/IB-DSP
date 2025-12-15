add_executable(sine_test sine_test.cpp)
target_link_libraries(sine_test PRIVATE IBDSP)
add_test(NAME sine_test COMMAND sine_test)

add_executable(square_wave_test square_wave_tests.cpp)
target_link_libraries(square_wave_test PRIVATE IBDSP)
add_test(NAME square_wave_test COMMAND square_wave_test)
