Name:           libdsc
Version:        0.1.0
Release:        1%{?dist}
Summary:        Essential Data Structures for C

License:        GPL-3.0-or-later
URL:            https://github.com/cm-jones/libdsc
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc
BuildRequires:  make
BuildRequires:  check-devel

%description
libdsc is an open-source C library featuring robust and efficient
implementations of essential data structures—including vectors, stacks, queues,
lists, sets, and maps—with interfaces that closely resemble those found in the
C++ standard library, which provides familiarity and ease of use to C++
developers.

%prep
%setup -q

%build
%make_build

%install
%make_install

%files
%license LICENSE
%doc README.md CHANGELOG.md
%{_libdir}/%{name}.so
%{_includedir}/dsc_*.h

%changelog
* Sat Apr 20 2024 Cody Michael Jones <codymjones@pm.me> - 0.1.0-1
- Initial release of libdsc
