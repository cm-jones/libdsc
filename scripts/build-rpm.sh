#!/usr/bin/env bash

# Exit on error, undefined variable, or pipe failure
set -euo pipefail

# Print commands being executed if DEBUG is set
if [[ "${DEBUG:-false}" == "true" ]]; then
    set -x
fi

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"

# Function to log messages
log() {
    local level=$1
    shift
    case "$level" in
        "INFO") printf "${GREEN}[INFO]${NC} %s\n" "$*" ;;
        "WARN") printf "${YELLOW}[WARN]${NC} %s\n" "$*" ;;
        "ERROR") printf "${RED}[ERROR]${NC} %s\n" "$*" ;;
    esac
}

# Check if we're in the correct directory
if [ ! -d "packaging/rpm" ]; then
    log "ERROR" "packaging/rpm directory not found"
    log "ERROR" "This script must be run from the project root directory"
    exit 1
fi

log "INFO" "Building RPM packages for libdsc..."

# Check for required tools
REQUIRED_TOOLS=(
    "rpmbuild:rpm-build"
    "cmake:cmake"
    "gcc:gcc"
    "rpmlint:rpmlint"
)

for tool in "${REQUIRED_TOOLS[@]}"; do
    IFS=":" read -r cmd pkg <<< "${tool}"
    if ! command -v "${cmd}" >/dev/null 2>&1; then
        log "ERROR" "${cmd} not found. Please install with: sudo dnf install ${pkg}"
        exit 1
    fi
done

# Set up RPM build environment
log "INFO" "Setting up RPM build environment..."
RPM_BUILD_ROOT="${HOME}/rpmbuild"
mkdir -p "${RPM_BUILD_ROOT}"/{BUILD,RPMS,SOURCES,SPECS,SRPMS}

# Create source tarball
VERSION=$(grep "Version:" packaging/rpm/libdsc.spec | awk '{print $2}')
log "INFO" "Creating source tarball for version ${VERSION}..."
git archive --format=tar.gz --prefix="libdsc-${VERSION}/" -o "${RPM_BUILD_ROOT}/SOURCES/libdsc-${VERSION}.tar.gz" HEAD

# Copy spec file
cp packaging/rpm/libdsc.spec "${RPM_BUILD_ROOT}/SPECS/"

# Create necessary documentation
if [ -x "$(command -v doxygen)" ]; then
    log "INFO" "Generating documentation..."
    doxygen docs/Doxyfile
else
    log "WARN" "Doxygen not found. Documentation package will be empty."
fi

# Build RPM packages
log "INFO" "Building RPM packages..."
rpmbuild -ba "${RPM_BUILD_ROOT}/SPECS/libdsc.spec"

# Verify packages
log "INFO" "Running package verification..."
if command -v rpmlint >/dev/null 2>&1; then
    for rpm in "${RPM_BUILD_ROOT}"/RPMS/*/*.rpm; do
        rpmlint "${rpm}" || log "WARN" "RPMLint reported issues with ${rpm}"
    done
    rpmlint "${RPM_BUILD_ROOT}/SPECS/libdsc.spec" || log "WARN" "RPMLint reported issues with spec file"
else
    log "WARN" "RPMLint not found. Skipping package verification."
fi

# Copy packages to current directory
log "INFO" "Copying packages to current directory..."
mkdir -p rpm-packages
cp "${RPM_BUILD_ROOT}"/RPMS/*/*.rpm rpm-packages/
cp "${RPM_BUILD_ROOT}"/SRPMS/*.rpm rpm-packages/

log "INFO" "Build complete! Packages are in rpm-packages/"
log "INFO" "To install the packages:"
log "INFO" "sudo dnf install rpm-packages/libdsc-*.rpm rpm-packages/libdsc-devel-*.rpm \\"
log "INFO" "                   rpm-packages/libdsc-debuginfo-*.rpm rpm-packages/libdsc-doc-*.rpm"

log "INFO" "To submit to a repository:"
log "INFO" "1. Create a Fedora/RHEL account if needed"
log "INFO" "2. Set up your GPG key: https://fedoraproject.org/wiki/Package_maintenance_guide"
log "INFO" "3. Submit package for review: https://bugzilla.redhat.com/enter_bug.cgi?product=Fedora&component=Package%20Review"
