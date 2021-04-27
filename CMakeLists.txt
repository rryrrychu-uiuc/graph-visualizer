cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(final-project)

set(CMAKE_CXX_STANDARD 11)

# This tells the compiler to not aggressively optimize and
# to include debugging information so that the debugger
# can properly read what's going on.
set(CMAKE_BUILD_TYPE Debug)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Warning flags
if(MSVC)
    # warning level 3 and all warnings as errors
    add_compile_options(/W3 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wpedantic -Werror)
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.11.1
)

# Adds Catch2 testing library
FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_library(catch2 INTERFACE src/visualizer/graph_manipulator_app.cpp include/visualizer/graph_manipulator_app.h src/core/graph.cpp include/core/graph.h apps/cinder_app_main.cpp src/core/node.cpp include/core/node.h tests/node_test.cpp tests/graph_test.cpp src/visualizer/graph_view.cpp include/visualizer/graph_view.h tests/edge_test.cpp)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif()

get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

list(APPEND CORE_SOURCE_FILES   src/core/graph.cpp
                                src/core/node.cpp
                                src/core/edge.cpp)

list(APPEND SOURCE_FILES    ${CORE_SOURCE_FILES}
        src/visualizer/graph_manipulator_app.cpp
                            src/visualizer/graph_view.cpp)

list(APPEND TEST_FILES  tests/node_test.cpp
                        tests/graph_test.cpp
                        tests/edge_test.cpp)

add_executable(visualize-graph apps/main.cpp ${CORE_SOURCE_FILES} src/core/edge.cpp include/core/edge.h)
target_include_directories(visualize-graph PRIVATE include)

ci_make_app(
        APP_NAME        graph-visualizer
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         apps/cinder_app_main.cpp ${SOURCE_FILES}
        INCLUDES        include
)

ci_make_app(
        APP_NAME        graph-visualizer-test
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         tests/test_main.cc ${SOURCE_FILES} ${TEST_FILES}
        INCLUDES        include
        LIBRARIES       catch2
)

if(MSVC)
    set_property(TARGET graph-visualizer-test APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:CONSOLE")
endif()