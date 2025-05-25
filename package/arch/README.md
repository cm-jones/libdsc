# Arch Linux Packaging for libdsc

This directory contains the Arch Linux packaging configuration for libdsc.

## Files

- `PKGBUILD` - Arch Linux package build script (synchronized with root PKGBUILD)

## Building Packages

From the project root directory, run:

```bash
./scripts/arch.sh
```

This script will:
1. Sync PKGBUILD files between root and package/arch/
2. Build the packages using makepkg
3. Verify packages with namcap
4. Generate .SRCINFO for AUR submission

## Package Structure

The build creates three packages:

- **libdsc** - Main library package
- **libdsc-docs** - Documentation package
- **libdsc-debug** - Debug symbols package

## AUR Submission

The root PKGBUILD is used for AUR submissions to maintain compatibility with standard Arch packaging workflows.

## Synchronization

The `scripts/arch.sh` script automatically keeps the PKGBUILD files synchronized:
- Root PKGBUILD is considered the source of truth
- Changes are automatically copied to package/arch/PKGBUILD
- If only package/arch/PKGBUILD exists, it's copied to root
