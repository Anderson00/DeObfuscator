cmake_minimum_required(VERSION 3.8)

set(PROJECT_SOURCES
    main.cpp
    resources/icons.qrc
    include/utils.h
    include/utils.cpp
    include/programfieldsmodel.h
    include/programfieldsmodel.cpp
    include/mainwindow.cpp
    include/mainwindow.ui
    include/subwindows/programheader.cpp
    include/subwindows/programheader.h
    include/subwindows/programheader.ui
    include/subwindows/debuggermain.cpp
    include/subwindows/debuggermain.h
    include/subwindows/debuggermain.ui)

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

target_link_libraries(Main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets cxxopts unicorn retdec)

#add_executable(Main main.cpp ${SOURCE_FILES_CURSES})

#target_link_libraries (Main PUBLIC cxxopts unicorn capstone-shared "${PROJECT_SOURCE_DIR}/lib/pdcurses.lib")
target_include_directories(Main PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/extern/unicorn/include"
                          #"${PROJECT_SOURCE_DIR}/extern/capstone/include"
                          "${PROJECT_SOURCE_DIR}/extern/retdec/include"
                          "include/"
                          )
