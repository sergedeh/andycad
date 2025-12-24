cmake_minimum_required(VERSION 3.10)
project(AndyCADCore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files in core directory
file(GLOB_RECURSE CORE_SOURCES 
    "core/*.cpp" 
    "core/*.c"
)

# Define the library
add_library(andycad_core STATIC ${CORE_SOURCES})

# Include directories
target_include_directories(andycad_core PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/core/utils
    ${CMAKE_CURRENT_SOURCE_DIR})

# Add all subdirectories of core to include path
file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/core ${CMAKE_CURRENT_SOURCE_DIR}/core/*)
foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/core/${child})
        target_include_directories(andycad_core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/${child})
    endif()
endforeach()

# Test executable
add_executable(core_test core_test.cpp)
target_link_libraries(core_test PRIVATE andycad_core)
