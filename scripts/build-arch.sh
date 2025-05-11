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
if [ ! -d "packaging/arch" ]; then
    log "ERROR" "packaging/arch directory not found"
    log "ERROR" "This script must be run from the project root directory"
    exit 1
fi

log "INFO" "Building Arch Linux packages for libdsc..."

# Check for required tools
REQUIRED_TOOLS=(
    "makepkg:base-devel"
    "cmake:cmake"
    "gcc:base-devel"
    "namcap:namcap"
)

for tool in "${REQUIRED_TOOLS[@]}"; do
    IFS=":" read -r cmd pkg <<< "${tool}"
    if ! command -v "${cmd}" >/dev/null 2>&1; then
        log "ERROR" "${cmd} not found. Please install with: sudo pacman -S ${pkg}"
        exit 1
    fi
done

# Clean any previous builds
log "INFO" "Cleaning previous build artifacts..."
rm -rf packaging/arch/pkg packaging/arch/src packaging/arch/*.tar.* packaging/arch/*.pkg.tar.zst

# Create necessary documentation
if [ -x "$(command -v doxygen)" ]; then
    log "INFO" "Generating documentation..."
    doxygen docs/Doxyfile
else
    log "WARN" "Doxygen not found. Documentation package will be empty."
fi

# Navigate to the arch packaging directory
cd packaging/arch

# Update .SRCINFO
log "INFO" "Updating .SRCINFO..."
makepkg --printsrcinfo > .SRCINFO

# Build packages
log "INFO" "Building packages..."
makepkg -f --noconfirm

# Verify packages
log "INFO" "Running package verification..."
if command -v namcap >/dev/null 2>&1; then
    for pkg in ./*.pkg.tar.zst; do
        namcap "${pkg}" || log "WARN" "Namcap reported issues with ${pkg}"
        namcap PKGBUILD || log "WARN" "Namcap reported issues with PKGBUILD"
    done
else
    log "WARN" "Namcap not found. Skipping package verification."
fi

log "INFO" "Build complete! Packages are in packaging/arch/"
log "INFO" "To install the packages:"
log "INFO" "sudo pacman -U libdsc-*.pkg.tar.zst libdsc-docs-*.pkg.tar.zst libdsc-debug-*.pkg.tar.zst"

log "INFO" "To upload to AUR:"
log "INFO" "1. Create AUR package: https://aur.archlinux.org/packages/submit"
log "INFO" "2. Clone AUR repo: git clone ssh://aur@aur.archlinux.org/libdsc.git"
log "INFO" "3. Copy PKGBUILD and .SRCINFO to the cloned repo"
log "INFO" "4. Commit and push to update the AUR"
