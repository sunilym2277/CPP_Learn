# 1. CMake Basics 
1. What CMake is a **cross-platform build system generator**.
2. How it differs from Make or Ninja:
    - CMake generates Makefiles or Ninja files; it doesn’t build by itself.
3. Role of CMakeList.txt - Defines project name, source files, targets (executables/libraries), include directories, link libraries.
4. Typical workflow :
```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles" to set compiler
cmake ..
cmake --build .
```

# 2. CMake Commands to Know

| Command | Purpose |
|---------|---------|
| `cmake ..` | Generate build system files from `CMakeLists.txt` |
| `cmake --build .` | Build the project (calls Make/Ninja/etc.) |
| `cmake -DCMAKE_BUILD_TYPE=Debug ..` | Specify Debug/Release build |
| `target_include_directories` | Specify header search paths for a target |
| `target_link_libraries` | Link a library to a target |
| `add_subdirectory()` | Include another CMake project/submodule |
| `find_package()` | Locate external libraries (system or installed packages) |


# 3. Common CMake Interview Questions
## 3.1 How do you create a CMake project with multiple .cpp files?
In CMake, you can create a project with multiple source files by listing all the `.cpp` files in the `add_executable()` or `add_library()` command.

## 3.2 Difference between `add_executable()` and `add_library()`

In CMake, these two commands are used to define **build targets**, but their purposes are different.

| Command | Purpose | Output | Typical Use Case |
|---------|---------|--------|-----------------|
| `add_executable()` | Defines an **executable target** | Generates an **executable** (`.exe` on Windows, no extension on Linux/macOS) | Programs that can be run directly by the user |
| `add_library()` | Defines a **library target** | Generates a **static library** (`.a` / `.lib`) or **shared library** (`.so` / `.dll`) | Reusable code for multiple programs, or shared modules |

### Example

```cmake
# Executable target
add_executable(MyApp main.cpp utils.cpp)

# Static library target
add_library(MyLib STATIC utils.cpp)

# Shared library target
add_library(MySharedLib SHARED utils.cpp)
```

## 3.2.1 Using utils.cpp directly in add_executable()
```cmake
Using utils.cpp directly in add_executable()
```
- utils.cpp is compiled along with the executable.
- All functions and code in utils.cpp are part of the final executable.
- Linking is done at compile time automatically.
- No separate library file is created.
- The executable is self-contained — you don’t need anything extra at runtime.

This is called static inclusion at compile time.

## 3.2.2 Creating a library (.lib / .a / .so / .dll) and linking it
```cmake
add_library(MyLib STATIC utils.cpp)   # or SHARED for dynamic library
add_executable(MyApp main.cpp)
target_link_libraries(MyApp PRIVATE MyLib)
```

- utils.cpp is compiled into the library first.
- MyApp only links to the compiled library, not the source file.
- If it’s a static library (STATIC), the compiled code from the library is copied into the executable at compile/link time, so no runtime dependency.
- If it’s a shared/dynamic library (SHARED), the executable contains references to the library, and the .so / .dll must be present at runtime.
✅ This is called static linking (for STATIC) or dynamic linking (for SHARED) depending on the library type.



## 3.3 How do you specify include directories? (`target_include_directories`)

In CMake, you can tell the compiler where to look for **header files** using the `target_include_directories()` command.  

### Syntax

```cmake
target_include_directories(<target> 
    [SYSTEM|PUBLIC|PRIVATE|INTERFACE] 
    <directories>...
)
```
Key Concepts

Target – The executable or library target that needs the headers.

Directories – Paths to the folders containing .hpp / .h files.

Scope Keywords:

PRIVATE → Only the target itself uses these headers.

PUBLIC → Both the target and anything linking to it can use these headers.

INTERFACE → Only the consumers (linking targets) use these headers, not the target itself.

SYSTEM → Treat the headers as system headers (suppress warnings from them).

## 3.4 How to link external libraries? (`target_link_libraries`)

In CMake, the `target_link_libraries()` command is used to **link libraries** (static or shared) to an executable or library target.  

### Syntax

```cmake
target_link_libraries(<target>
    [PRIVATE|PUBLIC|INTERFACE]
    <library1> <library2> ...
)
```

## 3.5 How to generate Debug vs Release builds?

In CMake, you can **specify the build type** when configuring the project. This controls compiler flags, optimizations, and debug symbols.  

### Setting Build Type

```bash
# Debug build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build
cmake -DCMAKE_BUILD_TYPE=Release ..
```

## 3.6 How does CMake find packages like Boost or OpenCV? (`find_package`)

CMake’s `find_package()` command is used to **locate and configure external libraries** and dependencies in a portable way.

---

### Syntax

```cmake
find_package(<PackageName> [version] [REQUIRED] [COMPONENTS <comp1> <comp2> ...])
```

## 3.7 How do you include subdirectories? (`add_subdirectory`)

CMake allows you to **organize a project into multiple subdirectories** and include them in the main build using `add_subdirectory()`.  

This is useful for modular projects, libraries, or separate components.

---

### Syntax

```cmake
add_subdirectory(<source_dir> [binary_dir] [EXCLUDE_FROM_ALL])
```

## 3.8 What are CMake variables and cache variables?

CMake uses **variables** to store values like paths, compiler flags, options, or configuration settings.  
There are **normal (local) variables** and **cache variables**.

---

### 1️⃣ Normal (Local) Variables

- Defined with `set()` in a `CMakeLists.txt` file.
- Scope: **current directory and subdirectories included after the definition** (unless overridden).  
- Not preserved across CMake runs (re-generated on each `cmake` invocation).  

#### Example:

```cmake
set(SRC_FILES main.cpp utils.cpp)
add_executable(MyApp ${SRC_FILES})
```


### 2 CACHE Variables

- Defined with `set()` in a `CMakeLists.txt` file.
set(VARIABLE_NAME VALUE CACHE TYPE "Documentation String" [FORCE])

#### Example:

```# 3. Define a string variable with a default value
set(USER_NICKNAME "Guest" CACHE STRING "Nickname for the build owner")
```


## 3.9 How do you use CMake presets or toolchain files for cross-platform builds?

CMake supports **presets** and **toolchain files** to make builds reproducible and cross-platform.  

---

### 1️⃣ CMake Toolchain Files

- A **toolchain file** defines **compilers, system paths, and build options** for a specific target platform.
- Useful when building for a platform different from the host (cross-compiling).

#### Example: `arm-toolchain.cmake`
```cmake
# Specify cross-compiler
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
set(CMAKE_FIND_ROOT_PATH /opt/arm/sysroot)

# Optional: search paths for libraries and headers
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```

## 3.10 How does CMake differ from Make/Ninja?
CMake is often confused with Make or Ninja, but they serve different purposes in the build workflow.

---

### 1️⃣ CMake

- **Type:** Build system **generator**  
- **Purpose:** Generates platform-specific build scripts or files for tools like Make, Ninja, or MSBuild.  
- **Input:** `CMakeLists.txt` (describes project structure, targets, dependencies, options)  
- **Output:** Build files (`Makefile`, `build.ninja`, `.sln`, etc.) that the underlying tool can execute.  
- **Cross-platform:** Yes, works across Linux, Windows, macOS.  

**Example:**
```bash
cmake -S . -B build          # Generate build system files in "build" directory
cmake --build build          # Build using generated build system (Make/Ninja/etc.)
```
✅ Summary

CMake → Defines what and how to build in a portable way.

Make / Ninja → Actually executes the build commands.

For modern C++ projects, typically CMake generates Ninja or Makefiles, and then Ninja/Make performs the build.

# 4. Practical Examples - Single executable from multiple files
```bash
cmake_minimum_required(VERSION 3.15)
project(MyApp)

add_executable(MyApp main.cpp utils.cpp)

target_include_directories(MyApp PRIVATE include)
```

- Linking an external library:
```bash
find_package(Boost REQUIRED)
target_link_libraries(MyApp PRIVATE Boost::boost)
```
Debug vs Release:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```


# 5. Cmake Practical

```bash
mkdir build
cd build
```

## Generate build files using CMake with MinGW
``` build
cmake -G "MinGW Makefiles" -S .. -B .
```
Explanation:

- -G "MinGW Makefiles" → Tells CMake to use MinGW Makefiles as the build system generator.
- -S .. → Source directory is one level up (where your CMakeLists.txt is located).
- -B . → Build directory is the current folder (your build folder).

What happens:

CMake detects compilers (C/C++), features, and your project structure. It generates Makefiles in the build folder. It does not compile yet.

## Build the project
```bash
cmake --build .
```
Explanation:

Tells CMake to execute the build in the current folder using the previously generated Makefiles.

What happens:
- Each .cpp or .c file is compiled into object files (.obj on Windows/MinGW).
- Libraries (STATIC / .a) are built.
- Executables are linked.
In your case:
- simple_sdk.c → compiled → libsimple_sdk.a (static library)
- demo.cpp → compiled → linked → bin\demo.exe