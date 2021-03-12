cmake_minimum_required(VERSION 3.5)

set(PROJECT_SOURCES
    main.cpp
    include/mainwindow.cpp
    include/mainwindow.ui
    include/programheader.cpp
    include/programheader.ui)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Main
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Main SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Main
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets cxxopts unicorn capstone-shared)

#add_executable(Main main.cpp ${SOURCE_FILES_CURSES})

#target_link_libraries (Main PUBLIC cxxopts unicorn capstone-shared "${PROJECT_SOURCE_DIR}/lib/pdcurses.lib")
target_include_directories(Main PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/extern/unicorn/include"
                          "${PROJECT_SOURCE_DIR}/extern/capstone/include"
                          "${PROJECT_SOURCE_DIR}/extern/retdec/include"
                          "include/"
                          )
