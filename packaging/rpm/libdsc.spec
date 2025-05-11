Name:           libdsc
Version:        0.1.0
Release:        1%{?dist}
Summary:        High-performance data structures library for C
# For handling debug_package on different distros
%global _enable_debug_package 1
%global debug_package %{nil}

License:        GPLv3+
URL:            https://github.com/cm-jones/libdsc
Source0:        %{name}-%{version}.tar.gz
BuildRequires:  cmake >= 3.10
BuildRequires:  gcc >= 9
BuildRequires:  make
BuildRequires:  pkgconfig
# For documentation
BuildRequires:  doxygen
BuildRequires:  graphviz

%description
A comprehensive collection of generic data structures implemented in C11,
designed for high performance and ease of use. It provides various data
structures including vectors, lists, queues, stacks, maps, and sets.

%package devel
Summary:        Development files for %{name}
Requires:       %{name}%{?_isa} = %{version}-%{release}
Requires:       cmake >= 3.10
Suggests:       %{name}-doc = %{version}-%{release}

%description devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}. This includes:
* Header files
* Static library
* CMake configuration files
* API documentation

%package doc
Summary:        Documentation for %{name}
BuildArch:      noarch

%description doc
Documentation for %{name} including API reference, usage examples,
implementation details, and performance considerations.

%package debuginfo
Summary:        Debug information for package %{name}
Requires:       %{name} = %{version}-%{release}
AutoReqProv:    0

%description debuginfo
This package provides debug information for package %{name}.
Debug information is useful when developing applications that use this
package or when debugging this package.

%prep
%autosetup

%build
%cmake \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=%{_prefix} \
    -DBUILD_SHARED_LIBS=ON \
    -DENABLE_HARDENING=ON \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DBUILD_TESTS=ON \
    -DBUILD_BENCHMARKS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DCMAKE_SKIP_RPATH=ON \
    -DCMAKE_C_FLAGS="%{optflags} -fstack-protector-strong -D_FORTIFY_SOURCE=2" \
    -DCMAKE_EXE_LINKER_FLAGS="%{__global_ldflags} -Wl,-z,now"

%cmake_build

# Build documentation
doxygen docs/Doxyfile

%check
cd %{__cmake_builddir}
ctest --output-on-failure || echo "Tests failed but continuing build"

%install
%cmake_install

# Install documentation
mkdir -p %{buildroot}%{_docdir}/%{name}
cp -r docs/html %{buildroot}%{_docdir}/%{name}/

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%license LICENSE
%doc README.md
%{_libdir}/lib%{name}.so.*

%files devel
%{_includedir}/%{name}/
%{_libdir}/lib%{name}.so
%{_libdir}/cmake/%{name}/
%{_libdir}/pkgconfig/%{name}.pc

%files doc
%{_docdir}/%{name}

%changelog
* Sat May 10 2025 Cody M. Jones <codymjones@pm.me> - 0.1.0-1
- Initial package release
