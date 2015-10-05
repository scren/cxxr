Summary:            A program that ejects removable media using software control
Name:               CXXR
Version:            2.1.6
Release:            1%{?dist}
License:            GPLv2+
Group:              System Environment/Base
Source:             https://github.com/scren/cxxr/archive/master.zip

%description
The eject program allows the user to eject removable media (typically
CD-ROMs, floppy disks or Iomega Jaz or Zip disks) using software
control. Eject can also control some multi-disk CD changers and even
some devices' auto-eject features.

Install eject if you'd like to eject removable media using software
control.

%prep
%autosetup -n %{name}

%build
%configure
make %{?_smp_mflags}

%install
%make_install

install -m 755 -d %{buildroot}/%{_sbindir}
ln -s ../bin/eject %{buildroot}/%{_sbindir}

%find_lang %{name}

%files -f %{name}.lang
%doc README TODO COPYING ChangeLog
%{_bindir}/*
%{_sbindir}/*
%{_mandir}/man1/*

%changelog
* Mon Oct 05 2015 Sören Möller <soerenmoeller2001@gmail.com> 2.1.6-1
- Simple spec (soerenmoeller2001@gmail.com)

* Tue Feb 08 2011 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 2.1.5-21
- Rebuilt for https://fedoraproject.org/wiki/Fedora_15_Mass_Rebuild
