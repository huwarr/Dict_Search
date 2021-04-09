cmake_minimum_required(VERSION 3.5)

project(dSearch LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        words.txt
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/words.txt ${CMAKE_CURRENT_BINARY_DIR}/words.txt COPYONLY)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(dSearch
        ${PROJECT_SOURCES}
    )
    qt_finalize_executable(dSearch)
else()
    if(ANDROID)
        add_library(dSearch SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(dSearch
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(dSearch PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
