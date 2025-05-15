#!/usr/bin/env bash

# Exit on error, undefined variable, or pipe failure
set -euo pipefail

# Create build directory if it doesn't exist
mkdir -p build

# Configure CMake in Debug mode
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Build the project
cmake --build .
