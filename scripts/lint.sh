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

# Check for required tools
if ! command -v clang-tidy &> /dev/null; then
    log "ERROR" "clang-tidy not found. Please install clang-tidy."
    exit 1
fi

if ! command -v cmake &> /dev/null; then
    log "ERROR" "cmake not found. Please install cmake."
    exit 1
fi

# Check if we're in the correct directory
if [ ! -f ".clang-tidy" ]; then
    log "ERROR" ".clang-tidy not found"
    log "ERROR" "This script must be run from the project root directory"
    exit 1
fi

# Generate compile_commands.json if it doesn't exist
if [ ! -f "build/compile_commands.json" ]; then
    log "INFO" "Generating compilation database..."
    cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
fi

log "INFO" "Running clang-tidy..."

# Find all .c and .h files
# Excluding build directory and third-party code
find . \
    -type f \( -name "*.c" -o -name "*.h" \) \
    -not -path "./build/*" \
    -not -path "./third-party/*" \
    -print0 | while IFS= read -r -d '' file; do
    log "INFO" "Checking ${file}..."
    clang-tidy \
        -p build \
        --config-file=.clang-tidy \
        "${file}" \
        || log "WARN" "clang-tidy reported issues with ${file}"
done

log "INFO" "Linting complete!"
