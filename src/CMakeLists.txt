cmake_minimum_required(VERSION 3.1)

set(SOURCE_FILES_CURSES include/curses/window.cpp include/curses/viewgroup.cpp include/curses/borderpane.cpp)

add_executable(Main main.cpp ${SOURCE_FILES_CURSES})

target_link_libraries (Main PUBLIC cxxopts unicorn capstone-shared "${PROJECT_SOURCE_DIR}/lib/pdcurses.lib")
target_include_directories(Main PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/extern/unicorn/include"
                          "${PROJECT_SOURCE_DIR}/extern/capstone/include"
                          "include/curses"
                          "${PROJECT_SOURCE_DIR}/extern/PDCurses/"                          
                          )