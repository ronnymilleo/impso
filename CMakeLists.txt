# =============================================================================
# PSO
# =============================================================================
# Particle Swarm Optimization Implementation
#
# Author: Ronny Milleo
# License: See LICENSE file in project root
# =============================================================================

cmake_minimum_required(VERSION 3.28)

# Project definition with version and metadata
project(PSO
    VERSION 0.1.0
    DESCRIPTION "Particle Swarm Optimization Implementation"
    LANGUAGES CXX  # Change to C for C projects
)

# =============================================================================
# C++ Standard and Compiler Requirements
# =============================================================================

# Require modern C++ standard
set(CMAKE_CXX_STANDARD 23)  # Adjust as needed (17, 20, 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Disable compiler-specific extensions

# =============================================================================
# Default Build Type
# =============================================================================

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# =============================================================================
# Project Options
# =============================================================================

option(PSO_BUILD_TESTS "Build unit tests" ON)
option(PSO_BUILD_EXAMPLES "Build example programs" ON)

# =============================================================================
# Compiler Configuration
# =============================================================================

# Enable compile commands export for IDE support (clangd, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set output directories for better organization
string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_LOWER)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${BUILD_TYPE_LOWER}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${BUILD_TYPE_LOWER}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${BUILD_TYPE_LOWER}/lib")

# =============================================================================
# Formatting Target (clang-format)
# =============================================================================

find_program(CLANG_FORMAT NAMES clang-format)
if(CLANG_FORMAT)
    # Collect all source files for formatting
    file(GLOB_RECURSE ALL_SOURCE_FILES 
        ${CMAKE_SOURCE_DIR}/application/*.cpp
        ${CMAKE_SOURCE_DIR}/application/*.h
        ${CMAKE_SOURCE_DIR}/library/src/*.cpp
        ${CMAKE_SOURCE_DIR}/library/src/*.cc
        ${CMAKE_SOURCE_DIR}/library/src/*.c
        ${CMAKE_SOURCE_DIR}/library/include/*.h
        ${CMAKE_SOURCE_DIR}/library/include/*.hpp
        ${CMAKE_SOURCE_DIR}/tests/*.cpp
        ${CMAKE_SOURCE_DIR}/tests/*.cc
        ${CMAKE_SOURCE_DIR}/tests/*.c
        ${CMAKE_SOURCE_DIR}/examples/*.cpp
        ${CMAKE_SOURCE_DIR}/examples/*.cc
        ${CMAKE_SOURCE_DIR}/examples/*.c
    )
    
    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${ALL_SOURCE_FILES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Formatting source code with clang-format"
        VERBATIM
    )
else()
    message(STATUS "clang-format not found; skipping automatic source formatting")
    add_custom_target(format
        COMMAND ${CMAKE_COMMAND} -E echo "clang-format not found, skipping formatting"
    )
endif()

# =============================================================================
# Dependencies
# =============================================================================

add_subdirectory(vendor)

# =============================================================================
# Main Library Target
# =============================================================================

add_subdirectory(library)

# =============================================================================
# Main Executable Target
# =============================================================================

add_subdirectory(application)

# Add Windows resource file for icon on Windows
if(WIN32)
    set(WINDOWS_RESOURCES ${CMAKE_SOURCE_DIR}/resources.rc)
else()
    set(WINDOWS_RESOURCES "")
endif()

add_executable(impso
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${WINDOWS_RESOURCES}
)

target_include_directories(impso
    PRIVATE
        ${CMAKE_SOURCE_DIR}/application
        ${CMAKE_SOURCE_DIR}/library/include
)

target_link_libraries(impso 
    PRIVATE 
        app_gui
)

# Copy assets folder to output directory after build
add_custom_command(TARGET impso POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:impso>/assets
    COMMENT "Copying assets to output directory"
)

# =============================================================================
# Examples
# =============================================================================

if(PSO_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# =============================================================================
# Testing
# =============================================================================

if(PSO_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# =============================================================================
# Copy compile_commands.json to source dir (for clangd)
# =============================================================================

add_custom_target(copy_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
    COMMENT "Copying compile_commands.json to source dir for clangd"
    DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
)

# =============================================================================
# Project Summary
# =============================================================================

message(STATUS "")
message(STATUS "=== PSO Configuration ===")
message(STATUS "Project:              ${PROJECT_NAME}")
message(STATUS "Version:              ${PROJECT_VERSION}")
message(STATUS "Build type:           ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard:         ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler:             ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build tests:          ${PSO_BUILD_TESTS}")
message(STATUS "Build examples:       ${PSO_BUILD_EXAMPLES}")
message(STATUS "=========================================")
message(STATUS "")

# =============================================================================
# End of file
# =============================================================================
