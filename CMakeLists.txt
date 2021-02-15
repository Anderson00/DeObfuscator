cmake_minimum_required(VERSION 3.1)
project(test)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

add_subdirectory(unicorn)
add_subdirectory(capstone)

add_executable(Main main.cpp )

target_link_libraries (Main PUBLIC unicorn capstone-shared "${PROJECT_SOURCE_DIR}/lib/pdcurses.lib")
target_include_directories(Main PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/unicorn/include"
                          "${PROJECT_SOURCE_DIR}/capstone/include"
                          "${PROJECT_SOURCE_DIR}/PDCurses-3.9/"
                          )