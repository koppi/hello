cmake_minimum_required(VERSION 3.22.0)

if(WIN32 AND NOT DEFINED CI)
  set(CMAKE_PREFIX_PATH "C:/Users/Jakob Flierl/6.9.0/msvc2022_64/")
  #set(CMAKE_PREFIX_PATH "C:/Users/cishn/6.9.0/msvc2022_64/")
endif()

if(UNIX)
    set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/Qt6")
endif()

# Global variables describing the project.
string(TIMESTAMP YEAR "%Y")
string(TIMESTAMP DATE "%Y-%m-%d")

set(APP_NAME "Hello World")
set(APP_EMAIL "jakob.flierl@gmail.com")
set(APP_AUTHOR "Jakob Flierl")
set(APP_COPYRIGHT "\\251 2025-${YEAR} ${APP_AUTHOR}")
set(APP_REVERSE_NAME "io.github.koppi.hello")
set(APP_DONATE_URL "https://github.com/sponsors/koppi")
set(APP_VERSION "0.0.1")

set(APP_URL "https://github.com/koppi/hello")
set(APP_URL_ISSUES_NEW "https://github.com/koppi/hello/issues/new/choose")

project(app VERSION ${APP_VERSION} LANGUAGES CXX C)

# Basic C++ related behavior of cmake.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Core Widgets Xml)

file(GLOB_RECURSE SOURCES "src/*.h" "src/*.cpp")

qt_add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME}
        PROPERTIES AUTOMOC ON)

target_link_libraries(${PROJECT_NAME}
        PUBLIC Qt6::Core Qt6::Widgets Qt6::Xml)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(UNIX)
    add_compile_options(-fPIC)
endif()

if (WIN32)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES WIN32_EXECUTABLE ON)
endif()

if(APPLE)
    add_compile_options(-stdlib=libc++)
    add_link_options(-stdlib=libc++)
endif()

set(QT_COMPONENTS
        Core
        Gui
        Widgets
        Xml
)

set(APP_LOW_NAME "${CMAKE_PROJECT_NAME}")

# Pass common defines.
add_compile_definitions(
        APP_NAME="${APP_NAME}"
        APP_VERSION="${CMAKE_PROJECT_VERSION}"
        APP_URL="${APP_URL}"
        APP_LONG_NAME="${APP_NAME} ${CMAKE_PROJECT_VERSION}"
        APP_LOW_NAME="${APP_LOW_NAME}"
        APP_REVERSE_NAME="${APP_REVERSE_NAME}"
        APP_AUTHOR="${APP_AUTHOR}"
        APP_DONATE_URL="${APP_DONATE_URL}"
        APP_EMAIL="${APP_EMAIL}"
        APP_LOW_H_NAME=".${CMAKE_PROJECT_NAME}"
        APP_REVISION="${APP_REVISION}"
        APP_SYSTEM_NAME="${CMAKE_SYSTEM_NAME}"
        APP_SYSTEM_VERSION="${CMAKE_SYSTEM_PROCESSOR}"
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE AND NOT DEFINED CI)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy

"${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets Xml)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

