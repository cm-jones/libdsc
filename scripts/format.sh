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

# Check for clang-format
if ! command -v clang-format &> /dev/null; then
    log "ERROR" "clang-format not found. Please install clang-format."
    exit 1
fi

# Check if we're in the correct directory
if [ ! -f ".clang-format" ]; then
    log "ERROR" ".clang-format not found"
    log "ERROR" "This script must be run from the project root directory"
    exit 1
fi

log "INFO" "Formatting C source files..."

# Find all .c and .h files and format them
# Excluding build directory and third-party code
find . \
    -type f \( -name "*.c" -o -name "*.h" -o -name "*.cpp" \) \
    -not -path "./build/*" \
    -not -path "./third-party/*" \
    -exec clang-format -i --style=file {} +

log "INFO" "Formatting complete!"
