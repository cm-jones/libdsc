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
libdsc is an open-source C library featuring robust and efficient implementations
of essential data structures, including vectors, stacks, queues, lists, sets, and maps.

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
* Mon Jun 05 2023 Your Name <your.email@example.com> - 0.1.0-1
- Initial release of libdsc
