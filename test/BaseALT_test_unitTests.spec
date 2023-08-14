%define name BaseALT_test_unitTests
%define version 1.0
%define release 1

Name: %{name}
Version: %{version}
Release: %{release}%{?dist}
Summary: Compares selected branches from https://rdb.altlinux.org/api/
License: MIT
URL: https://github.com/Gerben100/BaseALT_test
Group: Development/Languages

BuildRequires: cmake
BuildRequires: gcc-c++
BuildRequires: libcurl-devel
BuildRequires: nlohmann-json-devel
BuildRequires: catch2-devel

%description
Tests for the library from https://rdb.altlinux.org/api/

%build
cd %{_sourcedir}/BaseALT_test_unitTests
cmake .
make
cp %{_sourcedir}/BaseALT_test_unitTests/test_test %{_builddir}/test_test

%install
mkdir -p %{buildroot}%{_bindir}
install -m 755 test_test %{buildroot}%{_bindir}

%files
%{_bindir}/test_test

%post
ldconfig

%postun
ldconfig
