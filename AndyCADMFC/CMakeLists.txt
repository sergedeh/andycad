cmake_minimum_required(VERSION 3.10)
project(AndyCADCore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ANDYCAD_WASM "Build for WebAssembly targets" OFF)
if(ANDYCAD_WASM)
    add_compile_definitions(ANDYCAD_WASM)
endif()

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
file(GLOB TEST_SOURCES
    "core_test.cpp"
    "tests/*.cpp"
)
set(TEST_EXTRA_SOURCES
    # Core files are now included via library link
)
add_executable(core_test ${TEST_SOURCES} ${TEST_EXTRA_SOURCES})
target_link_libraries(core_test PRIVATE andycad_core)
target_include_directories(core_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_include_directories(core_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core)

# Add all core subdirectories to the test include path for legacy headers.
file(GLOB test_children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/core ${CMAKE_CURRENT_SOURCE_DIR}/core/*)
foreach(child ${test_children})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/core/${child})
        target_include_directories(core_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/${child})
    endif()
endforeach()

enable_testing()
add_test(NAME core_test COMMAND core_test)

if(ANDYCAD_WASM)
    add_executable(andycad_wasm
        wasm/main_wasm.cpp
        wasm/CDC_WASM.cpp
    )
    target_link_libraries(andycad_wasm PRIVATE andycad_core)
    target_include_directories(andycad_wasm PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/wasm
        ${CMAKE_CURRENT_SOURCE_DIR}/core
        ${CMAKE_CURRENT_SOURCE_DIR}/core/utils
    )
    file(GLOB wasm_children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/core ${CMAKE_CURRENT_SOURCE_DIR}/core/*)
    foreach(child ${wasm_children})
        if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/core/${child})
            target_include_directories(andycad_wasm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core/${child})
        endif()
    endforeach()
    set_property(TARGET andycad_wasm APPEND_STRING PROPERTY LINK_FLAGS " -sALLOW_MEMORY_GROWTH=1")
    set_property(TARGET andycad_wasm APPEND_STRING PROPERTY LINK_FLAGS " -sEXPORTED_RUNTIME_METHODS=['UTF8ToString']")
    set_target_properties(andycad_wasm PROPERTIES SUFFIX ".html")
endif()
