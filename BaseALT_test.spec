%define name BaseALT_test
%define version 1.0
%define release 6

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

%description
Compares two selected branches with https://rdb.altlinux.org/api/ and outputs as a result: Packages that are in the first branch and not in the second, packages that are in the second and not in the first branch, and also displays those packages, the version-realis of which in the first branch is higher than in the second. For output, it creates an output folder and in it subfolders with the name of the architectures in which the results are stored

%build
cd %{_sourcedir}/BaseALT_test
cmake .
make
cp %{_sourcedir}/BaseALT_test %{_builddir}/test_task_main
cp %{_sourcedir}/BaseALT_test %{_builddir}/libtest_task.so

%install
mkdir -p %{buildroot}%{_bindir}
install -m 755 test_task_main %{buildroot}%{_bindir}
mkdir -p %{buildroot}%{_libdir}
install -m 755 libtest_task.so %{buildroot}%{_libdir}

%files
%{_libdir}/libtest_task.so
%{_bindir}/test_task_main

%post
ldconfig

%postun
ldconfig
