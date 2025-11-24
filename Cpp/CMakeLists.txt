cmake_minimum_required(VERSION 3.15)

# Project setup
project(DtStrct
    VERSION 1.0
    DESCRIPTION "Data Structures and Algorithms"
    LANGUAGES CXX
)

# Set C++ standard and compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project structure variables
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Create include directory if it doesn't exist
file(MAKE_DIRECTORY ${INCLUDE_DIR})

# Create an interface library for header-only data structures
add_library(DataStructures INTERFACE)

# Automatically collect all header files for the DataStructures library
file(GLOB_RECURSE DATA_STRUCTURES_HEADERS
    "${SRC_DIR}/Containers/**/*.h"
    "${SRC_DIR}/Containers/**/*.hpp"
)

target_sources(DataStructures INTERFACE
    ${DATA_STRUCTURES_HEADERS}
)

# Create a library for projects
add_library(Projects
    ${SRC_DIR}/Projects/Calculator/Calculator.cpp
)

target_sources(Projects
    PRIVATE
        ${SRC_DIR}/Projects/Calculator/facilities.h
)

# Set include directories for DataStructures (header-only)
target_include_directories(DataStructures INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# Set include directories for Projects
target_include_directories(Projects PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# Create the main executable
add_executable(${PROJECT_NAME} 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# Link libraries to the main executable
target_link_libraries(${PROJECT_NAME} PRIVATE 
    DataStructures
    Projects
)

# Installation
install(TARGETS ${PROJECT_NAME} DataStructures Projects
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY ${SRC_DIR}/ DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
