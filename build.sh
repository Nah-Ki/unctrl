#!/bin/bash
set -e

# Go to the script's directory
cd "$(dirname "$0")"

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Run CMake configure
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Build with all CPU cores
cmake --build . -- -j$(nproc)

echo "✅ Build complete. Binaries are in build/bin/"

