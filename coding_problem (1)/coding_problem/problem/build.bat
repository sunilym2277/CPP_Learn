@echo off
setlocal enabledelayedexpansion
REM Simple build script for Windows
REM Ultra-simplified analytics SDK demo

echo === Building Simplified Analytics SDK Demo ===

REM Clean up any previous build
if exist demo.exe del demo.exe

REM Try different compilers in order of preference
echo Trying to find a C++ compiler...

REM Try g++ first (MinGW, MSYS2, etc.)
where g++ >nul 2>&1
if %errorlevel% == 0 (
    echo Using g++...
    g++ -o demo.exe demo.cpp simple_sdk.c
    goto check_result
)

REM Try clang++ (LLVM)
where clang++ >nul 2>&1
if %errorlevel% == 0 (
    echo Using clang++...
    clang++ -o demo.exe demo.cpp simple_sdk.c
    goto check_result
)

REM Try Visual Studio cl.exe
where cl.exe >nul 2>&1
if %errorlevel% == 0 (
    echo Using Visual Studio cl.exe...
    cl /EHsc demo.cpp simple_sdk.c /Fe:demo.exe
    goto check_result
)

REM Try to find and setup Visual Studio environment
echo Searching for Visual Studio installation...
set "VS_YEARS=2022 2019 2017"
set "VS_EDITIONS=Enterprise Professional Community BuildTools"
for %%y in (%VS_YEARS%) do (
    for %%e in (%VS_EDITIONS%) do (
        set "VCVARS=C:\Program Files\Microsoft Visual Studio\%%y\%%e\VC\Auxiliary\Build\vcvarsall.bat"
        if exist "!VCVARS!" (
            echo Found Visual Studio %%y %%e, setting up environment...
            call "!VCVARS!" x64 >nul 2>&1
            where cl.exe >nul 2>&1
            if !errorlevel! == 0 (
                echo Using Visual Studio cl.exe...
                cl /EHsc demo.cpp simple_sdk.c /Fe:demo.exe
                goto check_result
            )
        )

        REM Also try x86 Program Files location
        set "VCVARS=C:\Program Files (x86)\Microsoft Visual Studio\%%y\%%e\VC\Auxiliary\Build\vcvarsall.bat"
        if exist "!VCVARS!" (
            echo Found Visual Studio %%y %%e, setting up environment...
            call "!VCVARS!" x64 >nul 2>&1
            where cl.exe >nul 2>&1
            if !errorlevel! == 0 (
                echo Using Visual Studio cl.exe...
                cl /EHsc demo.cpp simple_sdk.c /Fe:demo.exe
                goto check_result
            )
        )
    )
)

echo ❌ Error: No C++ compiler found!
echo Please install one of:
echo   - MinGW-w64 (g++)
echo   - LLVM (clang++)
echo   - Visual Studio with C++ workload (cl.exe)
echo.
echo For Visual Studio, make sure to:
echo   - Install "Desktop development with C++" workload
echo   - Or run this from "Developer Command Prompt"
exit /b 1

:check_result
REM Clean up any temporary files
if exist *.obj del *.obj >nul 2>&1
if exist *.pdb del *.pdb >nul 2>&1

if exist demo.exe (
    echo ✅ Build successful!
    echo.
    echo Run the demo with:
    echo   demo.exe
    echo.
    echo Or build and run in one command:
    echo   build.bat ^&^& demo.exe
) else (
    echo ❌ Build failed!
    exit /b 1
)