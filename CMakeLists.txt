cmake_minimum_required(VERSION 3.27.7 FATAL_ERROR)

set(APP_VERSION "0.0.43")

# global variables describing the project.
string(TIMESTAMP YEAR "%Y")
string(TIMESTAMP DATE "%Y-%m-%d")

set(APP_NAME "Hello World")
set(APP_EMAIL "jakob.flierl@gmail.com")
set(APP_AUTHOR "Jakob Flierl")
set(APP_COPYRIGHT "\\251 2025-${YEAR} ${APP_AUTHOR}")
set(APP_REVERSE_NAME "io.github.koppi.hello")
set(APP_DONATE_URL "https://github.com/sponsors/koppi")

set(APP_URL "https://github.com/koppi/hello")
set(APP_URL_ISSUES_NEW "https://github.com/koppi/hello/issues/new/choose")

if(WIN32 AND NOT DEFINED CI)
    set(CMAKE_PREFIX_PATH "C:/Users/Jakob Flierl/6.9.0/msvc2022_64/")
    #set(CMAKE_PREFIX_PATH "C:/Users/cishn/6.9.0/msvc2022_64/")
endif()

if(UNIX)
    set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/Qt6")
endif()

project(app VERSION ${APP_VERSION} LANGUAGES C CXX)

# Basic C++ related behavior of cmake.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE SOURCES "src/*.h" "src/*.cpp")
include_directories("src")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(UNIX)
  add_compile_options(-fPIC)
endif()

if(APPLE)
    add_compile_options(-stdlib=libc++)
    add_link_options(-stdlib=libc++)
endif()

if (NOT DEFINED WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=UTF-8 -fexec-charset=UTF-8 -Wall -DHAS_REMOTE_API=0 -DUSE_OS_TZDB=1")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fno-math-errno -ffinite-math-only")
endif()

# Global compilation switches.
option(REVISION_FROM_GIT "Get revision using `git rev-parse`." ON)

# Import Qt libraries.
set(QT6_MIN_VERSION 6.4.2)

set(QT_COMPONENTS
        Core
        Gui
        Network
        Widgets
        Xml
)

if (FORCE_COLORED_OUTPUT)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        add_compile_options(-fdiagnostics-color=always)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options(-fcolor-diagnostics)
    endif()
endif()

find_package(QT NAMES Qt6)
find_package(Qt6 ${QT6_MIN_VERSION} COMPONENTS ${QT_COMPONENTS} REQUIRED)

set(RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/res/res.qrc")

qt_add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt::Core Qt::Network Qt::Widgets Qt::Xml)

if(WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE TRUE)
endif()

# Load git commit hash.
if(REVISION_FROM_GIT AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
    execute_process(COMMAND "git" "rev-parse" "--short" "HEAD"
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_VARIABLE APP_REVISION
            ERROR_QUIET
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    message(STATUS "Detected git revision: '${APP_REVISION}'.")
endif()

set(APP_LOW_NAME "${CMAKE_PROJECT_NAME}")

# Pass common defines.
add_compile_definitions(
        APP_NAME="${APP_NAME}"
        APP_VERSION="${CMAKE_PROJECT_VERSION}"
        APP_URL="${APP_URL}"
        APP_LONG_NAME="${APP_NAME} v${CMAKE_PROJECT_VERSION}+${APP_REVISION}"
        APP_LOW_NAME="${APP_LOW_NAME}"
        APP_REVERSE_NAME="${APP_REVERSE_NAME}"
        APP_AUTHOR="${APP_AUTHOR}"
        APP_DONATE_URL="${APP_DONATE_URL}"
        APP_EMAIL="${APP_EMAIL}"
        APP_LOW_H_NAME=".${CMAKE_PROJECT_NAME}"
        APP_REVISION="${APP_REVISION}"
        APP_SYSTEM_NAME="${CMAKE_SYSTEM_NAME}"
        APP_SYSTEM_VERSION="${CMAKE_SYSTEM_PROCESSOR}"
        APP_URL_ISSUES_NEW="${APP_URL_ISSUES_NEW}"

        QT_USE_QSTRINGBUILDER
        QT_USE_FAST_CONCATENATION
        QT_USE_FAST_OPERATOR_PLUS
        UNICODE
        _UNICODE
)

# TODO Configure and copy some needed files, see:
# https://github.com/martinrotter/rssguard/blob/a12c3952c870d36e4dfe1a6b40500d62f73f9b0d/CMakeLists.txt#L305

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
    foreach (QT_LIB ${QT_COMPONENTS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

if(WIN32 AND NOT DEFINED CI)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_PREFIX_PATH}/bin/windeployqt.exe"
            --qmldir "${CMAKE_SOURCE_DIR}"
            "$<TARGET_FILE:${PROJECT_NAME}>"
    )
endif()
