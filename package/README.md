# libdsc Packaging

This directory contains packaging files and scripts for creating distribution packages of libdsc for various Linux distributions.

## Supported Package Formats

- **Debian/Ubuntu** (.deb packages)
- **Red Hat/Fedora/CentOS** (.rpm packages)
- **Arch Linux** (PKGBUILD)

## Package Structure

### Debian Packages (.deb)

The Debian packaging creates two packages:

- **libdsc0**: Runtime library package containing the shared library
- **libdsc-dev**: Development package containing headers, static library, pkg-config file, and CMake configuration

#### Files:
- `deb/control` - Package metadata and dependencies
- `deb/rules` - Build rules for debhelper
- `deb/changelog` - Package changelog
- `deb/compat` - Debhelper compatibility level
- `deb/copyright` - Copyright and license information
- `deb/libdsc0.install` - Files for runtime package
- `deb/libdsc-dev.install` - Files for development package

### RPM Packages (.rpm)

The RPM packaging creates two packages:

- **libdsc**: Runtime library package containing the shared library
- **libdsc-devel**: Development package containing headers, static library, pkg-config file, and CMake configuration

#### Files:
- `rpm/libdsc.spec` - RPM specification file

### Arch Linux Package

- **libdsc**: Single package containing both runtime and development files

#### Files:
- `arch/PKGBUILD` - Arch Linux package build script
- `arch/README.md` - Arch-specific documentation

## Building Packages

### Prerequisites

#### For Debian/Ubuntu packages:
```bash
sudo apt-get install devscripts build-essential debhelper
```

#### For RPM packages:
```bash
# Fedora/RHEL/CentOS
sudo dnf install rpm-build rpmdevtools

# openSUSE
sudo zypper install rpm-build
```

#### For Arch Linux packages:
```bash
sudo pacman -S base-devel
```

### Build Commands

#### Debian Packages
```bash
# From project root directory
./scripts/debian.sh
```

This will create:
- `libdsc_0.1.0-1_amd64.deb` (runtime package)
- `libdsc-dev_0.1.0-1_amd64.deb` (development package)

#### RPM Packages
```bash
# From project root directory
./scripts/rpm.sh
```

This will create:
- `libdsc-0.1.0-1.x86_64.rpm` (runtime package)
- `libdsc-devel-0.1.0-1.x86_64.rpm` (development package)
- `libdsc-0.1.0-1.src.rpm` (source package)

#### Arch Linux Package
```bash
# From project root directory
./scripts/arch.sh
```

This will create:
- `libdsc-0.1.0-1-x86_64.pkg.tar.zst`

## Package Contents

### Runtime Package (libdsc0/libdsc)
- `/usr/lib/*/libdsc.so.*` - Shared library

### Development Package (libdsc-dev/libdsc-devel)
- `/usr/include/libdsc/` - Header files
- `/usr/lib/*/libdsc.so` - Development symlink
- `/usr/lib/*/libdsc.a` - Static library
- `/usr/lib/*/pkgconfig/libdsc.pc` - pkg-config file
- `/usr/lib/*/cmake/libdsc/` - CMake configuration files

## Installation

### Debian/Ubuntu
```bash
# Install runtime package
sudo dpkg -i libdsc_0.1.0-1_amd64.deb

# Install development package
sudo dpkg -i libdsc-dev_0.1.0-1_amd64.deb

# Or install both at once
sudo dpkg -i libdsc*.deb
```

### Red Hat/Fedora/CentOS
```bash
# Install runtime package
sudo rpm -i libdsc-0.1.0-1.x86_64.rpm

# Install development package
sudo rpm -i libdsc-devel-0.1.0-1.x86_64.rpm

# Or install both at once
sudo rpm -i libdsc*.rpm
```

### Arch Linux
```bash
sudo pacman -U libdsc-0.1.0-1-x86_64.pkg.tar.zst
```

## Using the Library

After installation, you can use libdsc in your projects:

### With pkg-config
```bash
gcc $(pkg-config --cflags libdsc) -o myapp myapp.c $(pkg-config --libs libdsc)
```

### With CMake
```cmake
find_package(libdsc REQUIRED)
target_link_libraries(myapp libdsc::dsc)
```

## Maintenance

### Updating Version

1. Update the `VERSION` file in the project root
2. Update the changelog files:
   - `package/deb/changelog`
   - `package/rpm/libdsc.spec` (changelog section)
3. Rebuild packages using the scripts

### Adding Dependencies

- For Debian: Update `Build-Depends` and `Depends` in `package/deb/control`
- For RPM: Update `BuildRequires` and `Requires` in `package/rpm/libdsc.spec`
- For Arch: Update `depends` and `makedepends` in `package/arch/PKGBUILD`

## Quality Assurance

All packages are built with:
- Release optimization (-O3)
- Security hardening flags
- Proper library versioning
- Standard file locations
- Correct dependencies

The packages follow distribution-specific guidelines:
- Debian Policy Manual
- Fedora Packaging Guidelines
- Arch Linux Package Guidelines
