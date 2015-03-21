ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_DISTCHECK_CONFIGURE_FLAGS = --enable-gtk-doc

@GNOME_CODE_COVERAGE_RULES@

pkgconfigdir = $(libdir)/pkgconfig

%-$(API_VERSION).pc: %.pc
	cp $< $@

pkgconfig_in_files = libical-glib-$(API_VERSION).pc
pkgconfig_DATA = $(pkgconfig_in_files:.pc.in=-$(API_VERSION).pc)

NULL =

SUBDIRS = \
	src \
	tests \
	docs \
	$(NULL)

EXTRA_DIST =  \
	$(pkgconfig_DATA) \
	ChangeLog \
	enumtypes.c.template \
	enumtypes.h.template \
	$(NULL)

DISTCLEANFILES = \
	$(pkgconfig_in_files)

MAINTAINERCLEANFILES = \
	$(srcdir)/INSTALL \
	$(srcdir)/aclocal.m4 \
	$(srcdir)/autoscan.log \
	$(srcdir)/compile \
	$(srcdir)/config.guess \
	$(srcdir)/config.h.in \
	$(srcdir)/config.sub \
	$(srcdir)/configure.scan \
	$(srcdir)/depcomp \
	$(srcdir)/gtk-doc.make \
	$(srcdir)/install-sh \
	$(srcdir)/ltmain.sh \
	$(srcdir)/missing \
	$(srcdir)/mkinstalldirs \
	$(srcdir)/m4/gtk-doc.m4 \
	$(srcdir)/m4/intltool.m4 \
	$(srcdir)/m4/libtool.m4 \
	$(srcdir)/m4/ltoptions.m4 \
	$(srcdir)/m4/ltsugar.m4 \
	$(srcdir)/m4/ltversion.m4 \
	$(srcdir)/m4/lt~obsolete.m4 \
	$(NULL)

-include $(top_srcdir)/git.mk
