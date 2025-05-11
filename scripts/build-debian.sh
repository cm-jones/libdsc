#!/usr/bin/env bash

# Exit on error, undefined variable, or pipe failure
set -euo pipefail

# Script to build Debian packages for libdsc
# This script should be run from the project root directory

# Print commands being executed
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
if [ ! -d "packaging/debian" ]; then
    log "ERROR" "packaging/debian directory not found"
    log "ERROR" "This script must be run from the project root directory"
    exit 1
fi

log "INFO" "Building Debian packages for libdsc..."

# Check for required tools
REQUIRED_TOOLS=(
    "debuild:devscripts"
    "dpkg-buildpackage:dpkg-dev"
    "dh:debhelper"
    "cmake:cmake"
)

for tool in "${REQUIRED_TOOLS[@]}"; do
    IFS=":" read -r cmd pkg <<< "${tool}"
    if ! command -v "${cmd}" >/dev/null 2>&1; then
        log "ERROR" "${cmd} not found. Please install with: sudo apt-get install ${pkg}"
        exit 1
    fi
done

# Clean any previous builds
log "INFO" "Cleaning previous build artifacts..."
rm -rf packaging/debian/tmp packaging/debian/*.log packaging/debian/*.substvars packaging/debian/files packaging/debian/*.debhelper
rm -f ../libdsc_* ../libdsc-dev_* ../libdsc-dbg_* ../libdsc-doc_*

# Create symlink for debuild (required as it expects debian/ in root)
log "INFO" "Setting up build environment..."
if [ -L debian ]; then
    rm debian
fi
ln -s packaging/debian debian

# Create necessary documentation
if [ -x "$(command -v doxygen)" ]; then
    log "INFO" "Generating documentation..."
    doxygen docs/Doxyfile
else
    log "WARN" "Doxygen not found. Documentation package will be empty."
fi

# Build packages
log "INFO" "Running debuild..."
export DEB_BUILD_MAINT_OPTIONS="hardening=+all"
export DEB_BUILD_OPTIONS="parallel=$(nproc)"

# Target distribution can be overridden with DIST environment variable
DIST=${DIST:-stable}
log "INFO" "Building for distribution: ${DIST}"

# Build binary packages only (-B), unsigned (-us -uc)
debuild -us -uc --check-dirname-level=0 -B -d -sa

# Clean up symlink
rm debian

# Verify packages
log "INFO" "Running lintian..."
if command -v lintian >/dev/null 2>&1; then
    for deb in ../libdsc*.deb; do
        lintian "${deb}" || log "WARN" "Lintian reported issues with ${deb}"
    done
else
    log "WARN" "Lintian not found. Skipping package verification."
fi

log "INFO" "Build complete! Packages are in the parent directory"
log "INFO" "To install the packages:"
log "INFO" "sudo dpkg -i ../libdsc0_*.deb ../libdsc-dev_*.deb ../libdsc-dbg_*.deb ../libdsc-doc_*.deb"
