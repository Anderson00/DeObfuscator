cmake_minimum_required(VERSION 3.1)
project(DeObfuscatorTerminal)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

add_subdirectory(extern/unicorn)
add_subdirectory(extern/capstone)
add_subdirectory(extern/cxxopts)

if(WIN32)
    find_program(NMAKE "nmake")
    find_program(MAKE "make")
    if(NOT NMAKE)
        message(FATAL_ERROR "Nmake is not installed")
    else()
        message(STATUS "nmake FOUND!")
        execute_process(COMMAND "nmake /F extern/PDCurses/wincon/Makefile.vc"
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE NMAMKE_WINCON)
        if(NOT NMAMKE_WINCON)
            message(FATAL_ERROR "namke command error")
        endif(NOT NMAMKE_WINCON)
    endif(NOT NMAKE)
elseif(UNIX)
    #TODO: 
endif(WIN32)

add_executable(Main main.cpp)

target_link_libraries (Main PUBLIC cxxopts unicorn capstone-shared "${PROJECT_SOURCE_DIR}/lib/pdcurses.lib")
target_include_directories(Main PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/extern/unicorn/include"
                          "${PROJECT_SOURCE_DIR}/extern/capstone/include"
                          "${PROJECT_SOURCE_DIR}/extern/PDCurses/"
                          )