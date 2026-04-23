cmake_minimum_required(VERSION 3.10)

# Project configuration
project(AnalyticsSDKDemo
    VERSION 1.0.0
    DESCRIPTION "Simple Analytics SDK Demo for C++ Interview"
    LANGUAGES C CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set C standard for the SDK
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Compiler-specific options
if(MSVC)
    # Visual Studio specific options
    add_compile_options(/W4)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    # GCC/Clang options
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Create the SDK library
add_library(simple_sdk STATIC
    simple_sdk.c
    simple_sdk.h
)

# Set properties for the library
set_target_properties(simple_sdk PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)

# Create the demo executable
add_executable(demo
    demo.cpp
)

# Link the SDK to the demo
target_link_libraries(demo PRIVATE simple_sdk)

# Include directories
target_include_directories(simple_sdk PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Platform-specific configurations
if(WIN32)
    # Windows-specific settings
    set_target_properties(demo PROPERTIES
        WIN32_EXECUTABLE FALSE  # Console application
    )
elseif(UNIX)
    # Unix/Linux/macOS specific settings
    if(NOT APPLE)
        # Linux-specific libraries if needed
        # target_link_libraries(demo PRIVATE pthread)
    endif()
endif()

# Build type configurations
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Debug build settings
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
    if(MSVC)
        add_compile_options(/Od /Zi)
    else()
        add_compile_options(-g -O0)
    endif()
endif()

# Release build settings
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)
    if(MSVC)
        add_compile_options(/O2)
    else()
        add_compile_options(-O2)
    endif()
endif()

# Install targets (optional)
install(TARGETS demo
    RUNTIME DESTINATION bin
)

install(FILES simple_sdk.h
    DESTINATION include
)

install(TARGETS simple_sdk
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

# Print build information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "CXX Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")