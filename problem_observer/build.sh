#!/bin/bash
# Simple build script for macOS/Linux
# Ultra-simplified analytics SDK demo

echo "=== Building Simplified Analytics SDK Demo ==="

# Clean up any previous build
rm -f demo

# Try to compile with g++ first, then clang++
if command -v g++ &> /dev/null; then
    echo "Using g++..."
    g++ -o demo demo.cpp simple_sdk.c
    BUILD_RESULT=$?
elif command -v clang++ &> /dev/null; then
    echo "Using clang++..."
    clang++ -o demo demo.cpp simple_sdk.c
    BUILD_RESULT=$?
else
    echo "❌ Error: No C++ compiler found (g++ or clang++)"
    exit 1
fi

# Check if build succeeded
if [ $BUILD_RESULT -eq 0 ]; then
    echo "✅ Build successful!"
    echo ""
    echo "Run the demo with:"
    echo "  ./demo"
    echo ""
    echo "Or build and run in one command:"
    echo "  ./build.sh && ./demo"
else
    echo "❌ Build failed!"
    exit 1
fi