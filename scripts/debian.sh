#!/bin/bash
set -e

# Setup Debian package structure
mkdir -p package/deb/libdsc-dev/DEBIAN
mkdir -p package/deb/libdsc-dev/usr/lib
mkdir -p package/deb/libdsc-dev/usr/include

# Copy library files
cp build/libdsc.so package/deb/libdsc-dev/usr/lib/
cp -r include/libdsc package/deb/libdsc-dev/usr/include/

# Create control file
cat > package/deb/libdsc-dev/DEBIAN/control << EOF
Package: libdsc-dev
Version: ${DEB_VERSION}
Section: libdevel
Priority: optional
Architecture: amd64
Depends: libc6
Maintainer: libdsc Team
Description: Data Structures in C Library - Development files
 A comprehensive collection of data structures implemented in C.
 This package contains the development files.
EOF

# Create Debian package
cd package/deb
dpkg-deb --build libdsc-dev
mv libdsc-dev.deb libdsc_${DEB_VERSION}_amd64.deb
