Summary: Web Tutorial For Use In OpenSpeedShop-Live
Name: webtutorial
Version: 0.0.1
Release: 3
License: GPL
Group: Documentation
URL: http://www.openspeedshop.org/
Source: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
Prefix: /opt/doc

Requires(pre):  coreutils
Requires(preun):  coreutils
Requires(post): coreutils
Requires(postun): coreutils


%description
Sample Applications For Use In OpenSpeedShop-Live

%prep
if [ -d %{name}-%{version} ]; then
    rm -fr %{name}-%{version}
fi

%setup -q -n %{name}-%{version}

%build

%install
mkdir -p $RPM_BUILD_ROOT%{prefix}/{details,img,tutorials}

install -D -m ugo+rw index.html $RPM_BUILD_ROOT%{prefix}
install -D -m ugo+rw details/*.html $RPM_BUILD_ROOT%{prefix}/details
install -D -m ugo+rw img/*.* $RPM_BUILD_ROOT%{prefix}/img
install -D -m ugo+rw tutorials/*.html $RPM_BUILD_ROOT%{prefix}/tutorials
install -D -m ugo+rw tutorials/*.pdf $RPM_BUILD_ROOT%{prefix}/tutorials

%clean
if test x"$RPM_BUILD_ROOT" != x"/"; then
    rm -rf $RPM_BUILD_ROOT
fi

%files
%defattr(-,root,root,-)

%{prefix}/*

%changelog
* Thu Oct 27 2011 Jim Galarowicz <jeg@krellinst.org> - 0.0.1
- Add SC2011 tutorial slides webtutorial-0.0.1 - 3
* Thu Oct 7 2010 Jim Galarowicz <jeg@krellinst.org> - 0.0.1
- Add SC2010 tutorial slides webtutorial-0.0.1 - 2
* Tue Aug 4 2009 Jim Galarowicz <jeg@krellinst.org> - 0.0.1
- Minor tweaks and move to name webtutorial-0.0.1
* Fri Aug 29 2008 Samuel K. Gutierrez <samuel@lanl.gov> - 1.2.6
- Initial creation of RPM specification file.
