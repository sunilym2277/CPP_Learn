@echo off
REM CMake build script for Analytics SDK Demo on Windows

echo === Building Analytics SDK Demo with CMake ===

REM Create build directory
if not exist "build" (
    echo Creating build directory...
    mkdir build
)

cd build

REM Configure with CMake
echo Configuring project...
cmake .. -DCMAKE_BUILD_TYPE=Release

REM Check if configuration was successful
if %errorlevel% neq 0 (
    echo ❌ CMake configuration failed!
    exit /b 1
)

REM Build the project
echo Building project...
cmake --build . --config Release

REM Check if build was successful
if %errorlevel% neq 0 (
    echo ❌ Build failed!
    exit /b 1
)

echo ✅ Build successful!
echo.

REM Find and report executable location
if exist "bin\Release\demo.exe" (
    echo Executable location: bin\Release\demo.exe
    echo.
    echo Run the demo with:
    echo   cd build ^&^& bin\Release\demo.exe
    echo   or
    echo   .\build\bin\Release\demo.exe
) else if exist "bin\demo.exe" (
    echo Executable location: bin\demo.exe
    echo.
    echo Run the demo with:
    echo   cd build ^&^& bin\demo.exe
    echo   or
    echo   .\build\bin\demo.exe
) else if exist "Release\demo.exe" (
    echo Executable location: Release\demo.exe
    echo.
    echo Run the demo with:
    echo   cd build ^&^& Release\demo.exe
) else if exist "demo.exe" (
    echo Executable location: demo.exe
    echo.
    echo Run the demo with:
    echo   cd build ^&^& demo.exe
) else (
    echo Executable built successfully but location may vary by CMake generator
    echo Check the build directory for demo.exe
)

echo.
echo To clean and rebuild:
echo   rmdir /s /q build ^&^& build_cmake.bat