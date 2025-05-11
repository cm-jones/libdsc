#!/bin/sh

# Exit on error
set -e

# Create build directory if it doesn't exist
mkdir -p build

# Configure CMake in Debug mode
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Build the project
cmake --build .
