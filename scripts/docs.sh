#!/usr/bin/env bash

# Exit on error, undefined variable, or pipe failure
set -euo pipefail

# Go to the root directory of the project
cd "$(dirname "$0")/.."

# Create docs directory if it doesn't already exist
mkdir -p docs
cd docs

# Check if Doxygen is installed
if ! command -v doxygen &> /dev/null
then
    echo "Doxygen could not be found. Please install it to generate documentation."
    exit 1
fi

# Generate documentation
doxygen ../Doxyfile

echo "Documentation generated in docs/ directory"
