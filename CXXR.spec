Summary:            A program that ejects removable media using software control
Name:               CXXR
Version:            2.1.5
Release:            21%{?dist}
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
* Tue Feb 08 2011 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 2.1.5-21
- Rebuilt for https://fedoraproject.org/wiki/Fedora_15_Mass_Rebuild
