cmake_minimum_required(VERSION 3.20)

project(
    IBDSP
    VERSION 0.1.0
    LANGUAGES CXX
)

# -------------------------------
# C++ standard
# -------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -------------------------------
# Library target
# -------------------------------
add_library(IBDSP
    src/waveforms/sine.cpp
)

# -------------------------------
# Public include directory
# -------------------------------
target_include_directories(IBDSP
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# -------------------------------
# Warnings (good for learning)
# -------------------------------
if (MSVC)
    target_compile_options(IBDSP PRIVATE /W4)
else()
    target_compile_options(IBDSP PRIVATE -Wall -Wextra -Wpedantic)
endif()

# -------------------------------
# Optional: build as shared library
# -------------------------------
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# -------------------------------
# Install rules (optional, but pro)
# -------------------------------
install(
    TARGETS IBDSP
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(
    DIRECTORY include/
    DESTINATION include
)

enable_testing()

#add tests
add_subdirectory(tests)
