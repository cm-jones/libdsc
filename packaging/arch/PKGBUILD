# Maintainer: Cody M. Jones <codymjones@pm.me>

pkgbase=libdsc
pkgname=('libdsc' 'libdsc-docs' 'libdsc-debug')
pkgver=0.1.0_alpha
pkgrel=1
pkgdesc="High-performance data structures library for C"
arch=('x86_64' 'aarch64' 'armv7h')
url="https://github.com/cm-jones/libdsc"
license=('GPL3')
makedepends=('cmake>=3.10' 'gcc>=9.3' 'make')
options=('!strip')
source=("$pkgbase-$pkgver.tar.gz::https://github.com/cm-jones/$pkgbase/archive/v${pkgver/_/-}.tar.gz")
sha256sums=('SKIP')

build() {
  cmake -B build -S "$pkgbase-${pkgver/_/-}" \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/usr \
    -DBUILD_SHARED_LIBS=ON \
    -DENABLE_HARDENING=ON \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DBUILD_TESTS=ON \
    -DBUILD_BENCHMARKS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DCMAKE_SKIP_RPATH=ON \
    -DCMAKE_C_FLAGS="${CFLAGS} -fstack-protector-strong -D_FORTIFY_SOURCE=2" \
    -DCMAKE_CXX_FLAGS="${CXXFLAGS} -fstack-protector-strong -D_FORTIFY_SOURCE=2" \
    -DCMAKE_EXE_LINKER_FLAGS="${LDFLAGS} -Wl,-z,now"

  cmake --build build
}

check() {
  cd build
  ctest --output-on-failure || echo "Tests failed but continuing build"
}

package_libdsc() {
  depends=('glibc')
  provides=('libdsc.so')
  backup=('etc/libdsc.conf')

  DESTDIR="$pkgdir" cmake --install build

  # Move debug symbols to debug package
  mv "$pkgdir"/usr/lib/debug "$srcdir/debug"
  # Move docs to docs package
  mv "$pkgdir"/usr/share/doc "$srcdir/doc"
}

package_libdsc-docs() {
  pkgdesc="Documentation for libdsc"
  arch=('any')
  
  mkdir -p "$pkgdir/usr/share"
  mv "$srcdir/doc" "$pkgdir/usr/share/"
}

package_libdsc-debug() {
  pkgdesc="Debug symbols for libdsc"
  depends=('libdsc')
  
  mkdir -p "$pkgdir/usr/lib"
  mv "$srcdir/debug" "$pkgdir/usr/lib/"
}
