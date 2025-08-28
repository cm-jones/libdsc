#!/usr/bin/env bash
set -euo pipefail

# Build RPM packages using rpmbuild
# This script assumes you have the RPM packaging tools installed:
# sudo dnf install rpm-build rpmdevtools (Fedora/RHEL/CentOS)
# sudo zypper install rpm-build (openSUSE)

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

echo "Building RPM packages for libdsc version ${VERSION}"

# Setup RPM build environment
rpmdev-setuptree

# Create source tarball
# Validate package directory exists
if [ ! -f "package/rpm/libdsc.spec" ]; then
    echo "Error: package/rpm/libdsc.spec not found"
    exit 1
fi

echo "Creating source tarball..."
TEMP_DIR=$(mktemp -d)
PACKAGE_PATH="${TEMP_DIR}/${PACKAGE_DIR}"
mkdir -p "${PACKAGE_PATH}"

# Copy source files to package directory
cp -r . "${PACKAGE_PATH}/"
cd "${PACKAGE_PATH}"

# Remove build artifacts and git files
rm -rf build/ .git/ .github/

# Create tarball
cd "${TEMP_DIR}"
tar -czf "${PACKAGE_DIR}.tar.gz" "${PACKAGE_DIR}/"

# Copy tarball to RPM SOURCES directory
cp "${PACKAGE_DIR}.tar.gz" ~/rpmbuild/SOURCES/

# Copy spec file to RPM SPECS directory
cp "${PACKAGE_PATH}/package/rpm/libdsc.spec" ~/rpmbuild/SPECS/

# Build RPM packages
echo "Building RPM packages..."
cd ~/rpmbuild/SPECS
rpmbuild -ba libdsc.spec

echo "RPM packages built successfully!"
echo "Source RPM: ~/rpmbuild/SRPMS/libdsc-${VERSION}-1.*.src.rpm"
echo "Binary RPMs:"
ls -la ~/rpmbuild/RPMS/*/libdsc*-${VERSION}-1.*.rpm
