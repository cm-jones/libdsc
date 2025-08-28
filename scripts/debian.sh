#!/usr/bin/env bash
set -euo pipefail

# Build Debian packages using debuild
# This script assumes you have the debian packaging tools installed:
# sudo apt-get install devscripts build-essential debhelper

VERSION=$(cat VERSION)
PACKAGE_DIR="libdsc-${VERSION}"

# Cleanup function
cleanup() {
    if [[ -n "${TEMP_DIR:-}" && -d "${TEMP_DIR}" ]]; then
        echo "Cleaning up temporary directory: ${TEMP_DIR}"
        rm -rf "${TEMP_DIR}"
    fi
}
trap cleanup EXIT

echo "Building Debian packages for libdsc version ${VERSION}"

# Validate package directory exists
if [ ! -d "package/deb" ]; then
    echo "Error: package/deb directory not found"
    exit 1
fi

# Create temporary directory
TEMP_DIR=$(mktemp -d)
PACKAGE_PATH="${TEMP_DIR}/${PACKAGE_DIR}"

# Create source package directory
mkdir -p "${PACKAGE_PATH}"

# Copy source files to package directory
cp -r . "${PACKAGE_PATH}/"
cd "${PACKAGE_PATH}"

# Remove build artifacts and git files
rm -rf build/ .git/ .github/

# Copy debian packaging files to debian/ directory
mkdir -p debian/
cp package/deb/* debian/

# Make rules file executable
chmod +x debian/rules

# Build source package
echo "Building source package..."
debuild -S -us -uc

# Build binary packages
echo "Building binary packages..."
debuild -b -us -uc

echo "Debian packages built successfully!"
echo "Packages are located in ${TEMP_DIR}/"
ls -la "${TEMP_DIR}"/libdsc*
