#!/bin/bash

# CMake build script for Analytics SDK Demo
# Works on Linux, macOS, and Windows (with bash)

echo "=== Building Analytics SDK Demo with CMake ==="

# Create build directory
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

cd build

# Configure with CMake
echo "Configuring project..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# Check if configuration was successful
if [ $? -ne 0 ]; then
    echo "❌ CMake configuration failed!"
    exit 1
fi

# Build the project
echo "Building project..."
cmake --build . --config Release

# Check if build was successful
if [ $? -ne 0 ]; then
    echo "❌ Build failed!"
    exit 1
fi

echo "✅ Build successful!"
echo
echo "Executable location:"
if [ -f "bin/demo" ]; then
    echo "  bin/demo"
    echo
    echo "Run the demo with:"
    echo "  cd build && bin/demo"
    echo "  or"
    echo "  ./build/bin/demo"
elif [ -f "bin/Release/demo.exe" ]; then
    echo "  bin/Release/demo.exe"
    echo
    echo "Run the demo with:"
    echo "  cd build && bin/Release/demo.exe"
elif [ -f "bin/demo.exe" ]; then
    echo "  bin/demo.exe"
    echo
    echo "Run the demo with:"
    echo "  cd build && bin/demo.exe"
else
    echo "  demo (location may vary by platform)"
    echo
    echo "Run the demo with:"
    echo "  cd build && ./demo"
fi

echo
echo "To clean and rebuild:"
echo "  rm -rf build && ./build_cmake.sh"