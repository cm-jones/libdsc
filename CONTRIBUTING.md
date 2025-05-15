# Contributing to libdsc

## Development Environment

1. Clone the repository:
```bash
git clone https://github.com/cm-jones/libdsc.git
cd libdsc
```

2. Open in VSCode with Dev Containers extension to get a complete development environment with all tools pre-installed.

## Building and Testing

### Basic Build

```bash
./scripts/build.sh
```

### Run Tests

```bash
./scripts/build.sh
cd build
ctest --output-on-failure
```

### Run Linter

```bash
./scripts/lint.sh
```

### Format Code

```bash
./scripts/format.sh
```

## Package Management

### Official Releases

The recommended way to create releases is through GitHub:

1. Tag your version:
```bash
git tag v0.1.0
git push origin v0.1.0
```

2. GitHub Actions will automatically:
- Build source tarball
- Create Debian packages
- Create RPM packages
- Create Arch packages
- Upload all artifacts to the GitHub release

This ensures consistent, reproducible builds in a clean environment.

### Local Package Testing

For development and testing, you can build packages locally in the dev container:

#### Debian Package

```bash
./scripts/build-debian.sh
```
Outputs:
- libdsc0_*.deb (runtime)
- libdsc-dev_*.deb (development)

#### RPM Package

```bash
./scripts/build-rpm.sh
```
Outputs:
- libdsc-*.rpm (runtime)
- libdsc-devel-*.rpm (development)

Requirements:
- RPM-based system (Fedora/RHEL) or container
- rpm-build and rpmdevtools packages

#### Arch Package

```bash
./scripts/build-arch.sh
```
Outputs:
- libdsc-*.pkg.tar.zst (combined runtime/dev)

Requirements:
- Arch Linux system or container
- base-devel package group

Note: Local package builds are useful for testing but should not be distributed. Official packages should come from GitHub releases.

### Package Types and Content

1. Debian (.deb)
   - libdsc0: Runtime library
   - libdsc-dev: Development files (headers, cmake)

2. RPM (.rpm)
   - libdsc: Runtime library
   - libdsc-devel: Development files (headers, cmake)

3. Arch (.pkg.tar.zst)
   - Single package with both runtime and development files

### Version Numbering

- Release tags: v0.1.0
- Debian format: 0.1.0
- RPM format: 0.1.0
- Arch format: 0.1.0

## Adding New Features

1. Create a feature branch:
```bash
git checkout -b feature/my-feature
```

2. Make your changes
3. Run tests and linting
4. Submit a pull request

## Code Style

- Follow existing code formatting
- Use clang-format (configured in .clang-format)
- Run format.sh before committing
