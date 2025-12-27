# Add subdirectory for waveform tests
add_subdirectory(waveforms_tests)

add_executable(stateful_oscillators_test)
target_sources(stateful_oscillators_test PRIVATE stateful_osc_tests.cpp)
target_link_libraries(stateful_oscillators_test PRIVATE IBDSP)
add_test(NAME stateful_oscillators_test COMMAND stateful_oscillators_test)

add_executable(fft_tests)
target_sources(fft_tests PRIVATE fft_tests.cpp)
target_link_libraries(fft_tests PRIVATE IBDSP)
add_test(NAME fft_tests COMMAND fft_tests)