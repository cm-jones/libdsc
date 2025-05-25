Name:           libdsc
Version:        0.1.0
Release:        1%{?dist}
Summary:        Containers from the C++ Standard Library reimplemented in C

License:        GPL-3.0-or-later
URL:            https://github.com/cm-jones/libdsc
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  cmake >= 3.14
BuildRequires:  gcc
BuildRequires:  make
BuildRequires:  pkgconfig

%description
libdsc is a free and open-source C library featuring generic
implementations of containers from the C++ Standard Library.
The project aims to bring modern container functionality to the C programming
language with memory-safe, well-tested implementations.

%package        devel
Summary:        Development files for %{name}
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description    devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.

%prep
%autosetup

%build
%cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_TESTS=OFF \
    -DBUILD_BENCHMARKS=OFF \
    -DBUILD_EXAMPLES=OFF
%cmake_build

%install
%cmake_install

%check
# Tests are run in CI/CD pipeline

%ldconfig_scriptlets

%files
%license LICENSE
%doc README.md CHANGELOG.md
%{_libdir}/libdsc.so.*

%files devel
%{_includedir}/libdsc/
%{_libdir}/libdsc.so
%{_libdir}/libdsc.a
%{_libdir}/pkgconfig/libdsc.pc
%{_libdir}/cmake/libdsc/

%changelog
* Thu May 22 2025 Cody M. Jones <codymjones@pm.me> - 0.1.0-1
- Initial release of libdsc
- Generic data structure containers for C
- Implements vector, list, forward_list, stack, queue, unordered_map, unordered_set
- Memory-safe implementations with comprehensive error handling
- Modern CMake build system with pkg-config support
- Comprehensive API documentation and examples
- Professional project structure following industry best practices
