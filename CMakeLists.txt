cmake_minimum_required(VERSION 3.14)
project(MazeRouter CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output executables directly to the build/ directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# CRITICAL: enable_testing() MUST be before add_subdirectory() for tests
# We also place it before FetchContent to guarantee tests are registered for our project first
enable_testing()

# Fetch FTXUI for the terminal visualizer
include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG main
)
FetchContent_MakeAvailable(ftxui)

add_subdirectory(src)
add_subdirectory(test)