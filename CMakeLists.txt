cmake_minimum_required(VERSION 3.15)

# ----------------------------
# 1. Project setup
# ----------------------------
project(MyProject VERSION 1.0 LANGUAGES CXX C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ----------------------------
# 2. Build type configurations
# ----------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
    if(MSVC)
        add_compile_options(/Od /Zi)
    else()
        add_compile_options(-g -O0)
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)
    if(MSVC)
        add_compile_options(/O2)
    else()
        add_compile_options(-O2)
    endif()
endif()

# ----------------------------
# 3. Add source files
# ----------------------------
set(SRC_FILES
    src/main.cpp
    src/utils.cpp
    src/other.cpp
)

# ----------------------------
# 4. Create executable
# ----------------------------
add_executable(MyApp ${SRC_FILES})

# ----------------------------
# 5. Include directories
# ----------------------------
target_include_directories(MyApp PRIVATE
    include
)

# ----------------------------
# 6. Link external libraries
# ----------------------------
# Example: OpenCV
# find_package(OpenCV REQUIRED)
# if(OpenCV_FOUND)
#     target_include_directories(MyApp PRIVATE ${OpenCV_INCLUDE_DIRS})
#     target_link_libraries(MyApp PRIVATE ${OpenCV_LIBS})
# endif()

# Example: Boost
# find_package(Boost 1.82 REQUIRED COMPONENTS filesystem system)
# if(Boost_FOUND)
#     target_include_directories(MyApp PRIVATE ${Boost_INCLUDE_DIRS})
#     target_link_libraries(MyApp PRIVATE ${Boost_LIBRARIES})
# endif()

# ----------------------------
# 7. Include GitHub repo using FetchContent
# ----------------------------
include(FetchContent)

# Example: spdlog logging library
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.11.0
)

FetchContent_MakeAvailable(spdlog)
target_link_libraries(MyApp PRIVATE spdlog::spdlog)

# ----------------------------
# 8. Include subdirectories
# ----------------------------
# Example: local library folder
# add_subdirectory(external/mylib)   # mylib must have its own CMakeLists.txt
# target_link_libraries(MyApp PRIVATE mylib)

# ----------------------------
# 9. Output directories
# ----------------------------
set_target_properties(MyApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
