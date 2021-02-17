cmake_minimum_required(VERSION 3.1)
project(DeObfuscatorTerminal)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

add_subdirectory(extern/unicorn)
add_subdirectory(extern/capstone)
add_subdirectory(extern/cxxopts)
add_subdirectory(src)

if(WIN32)
    find_program(NMAKE "nmake")
    find_program(MAKE "make")
    if(NOT NMAKE)
        message(FATAL_ERROR "Nmake is not installed")
    else()
        message(STATUS "nmake FOUND!")
        #execute_process(COMMAND nmake /F Makefile.vc
        #                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/extern/PDCurses/wincon/
        #                RESULT_VARIABLE NMAMKE_WINCON)
        #execute_process(COMMAND "del *.obj"
        #                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/extern/PDCurses/wincon/)
        
        #if(NOT NMAMKE_WINCON)
        #    message(FATAL_ERROR "namke command error")
        #endif(NOT NMAMKE_WINCON)
    endif(NOT NMAKE)
elseif(UNIX)
    #TODO: 
endif(WIN32)

