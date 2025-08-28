#!/usr/bin/env bash

# Exit on error, undefined variable, or pipe failure
set -euo pipefail

echo "Building libdsc project..."

# Check if CMakeLists.txt exists
if [ ! -f "CMakeLists.txt" ]; then
    echo "Error: CMakeLists.txt not found in current directory"
    echo "Please run this script from the project root directory"
    exit 1
fi

# Create build directory if it doesn't exist
echo "Creating build directory..."
mkdir -p build

# Configure CMake in Debug mode
echo "Configuring CMake in Debug mode..."
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Build the project
echo "Building project..."
cmake --build .

echo "Build completed successfully!"
