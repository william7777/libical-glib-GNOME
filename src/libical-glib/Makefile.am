NULL =
CLEANFILES=
BUILT_SOURCES=

i-cal-object.c: i-cal-object.c.in
	cp $< $@

i-cal-object.h: i-cal-object.h.in
	cp $< $@

libical-glib.h: libical-glib.h.in
	cp $< $@

i-cal-timezone.h i-cal-timezone.c i-cal-enums.h i-cal-enums.c i-cal-property.h i-cal-property.c i-cal-component.h i-cal-component.c i-cal-timetype.h i-cal-timetype.c i-cal-time.h i-cal-time.c i-cal-array.h i-cal-array.c i-cal-attach.h i-cal-attach.c i-cal-duration-type.h i-cal-duration-type.c i-cal-error.h i-cal-error.c i-cal-memory.h i-cal-memory.c i-cal-mime.h i-cal-mime.c i-cal-parser.h i-cal-parser.c i-cal-value.h i-cal-value.c i-cal-derived-value.h i-cal-derived-value.c i-cal-parameter.h i-cal-parameter.c i-cal-period-type.h i-cal-period-type.c: 
	$(top_builddir)/src/build-tools/src-generator "$(top_builddir)/src/build-tools" "$(top_builddir)/src/api" i-cal-timezone.xml i-cal-enums.xml i-cal-property.xml i-cal-component.xml i-cal-timetype.xml i-cal-time.xml i-cal-array.xml i-cal-attach.xml i-cal-duration-type.xml i-cal-error.xml i-cal-memory.xml i-cal-mime.xml i-cal-parser.xml i-cal-value.xml i-cal-derived-value.xml i-cal-parameter.xml i-cal-period-type.xml

lib_LTLIBRARIES = libical-glib-1.0.la

libical_glib_1_0_la_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	-I$(top_srcdir)/src \
	-I$(top_builddir)/src \
	-DG_LOG_DOMAIN=\"libical-glib\" \
	-DLIBICAL_GLIB_COMPILATION=1 \
	$(GLIB_CFLAGS) \
	$(GOBJECT2_CFLAGS) \
	$(LIBICAL_CFLAGS) \
	$(CODE_COVERAGE_CFLAGS) \
	$(NULL)

libical_glib_1_0_la_LIBADD = \
	$(GLIB_LIBS) \
	$(LIBICAL_LIBS) \
	$(GOBJECT2_LIBS) \
	$(NULL)

libical_glib_1_0_la_LDFLAGS = -avoid-version $(NO_UNDEFINED) \
	$(CODE_COVERAGE_LDFLAGS) \
	$(NULL)

libical_glib_1_0_la_SOURCES = \
	i-cal-object.c \
	i-cal-enums.c \
	i-cal-timezone.c \
	i-cal-component.c \
	i-cal-property.c \
	i-cal-timetype.c \
	i-cal-time.c \
	i-cal-array.c \
	i-cal-attach.c \
	i-cal-duration-type.c \
	i-cal-error.c \
	i-cal-memory.c \
	i-cal-mime.c \
	i-cal-parser.c \
	i-cal-value.c \
	i-cal-derived-value.c \
	i-cal-parameter.c \
	i-cal-period-type.c \
	$(NULL)

privinclude_HEADERS = \
	libical-glib.h \
	i-cal-object.h \
	i-cal-enums.h \
	i-cal-timezone.h \
	i-cal-component.h \
	i-cal-property.h \
	i-cal-timetype.h \
	i-cal-time.h \
	i-cal-array.h \
	i-cal-attach.h \
	i-cal-duration-type.h \
	i-cal-error.h \
	i-cal-memory.h \
	i-cal-mime.h \
	i-cal-parser.h \
	i-cal-value.h \
	i-cal-derived-value.h \
	i-cal-parameter.h \
	i-cal-period-type.h \
	$(NULL)

BUILT_SOURCES += \
	$(libical_glib_1_0_la_SOURCES) \
	$(privinclude_HEADERS) \
	$(NULL)

-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = \
	--add-include-path=$(top_builddir)/src/libical-glib \
	--add-include-path=$(srcdir) \
	--identifier-prefix=ICal \
	--pkg-export libical-glib-1.0 \
	--c-include="libical-glib/libical-glib.h" \
	$(NULL)
INTROSPECTION_COMPILER_ARGS = \
	--includedir=$(srcdir) \
	$(NULL)

if HAVE_INTROSPECTION
introspection_sources = $(libical_glib_1_0_la_SOURCES)
ICalGLib-1.0.gir: libical-glib-1.0.la

ICalGLib_1_0_gir_INCLUDES = GObject-2.0 GLib-2.0
ICalGLib_1_0_gir_CFLAGS = \
	$(INCLUDES) \
	-I$(top_srcdir)/src \
	-I$(top_builddir)/src \
	$(GLIB_CFLAGS) \
	$(GOBJECT2_CFLAGS) \
	$(LIBICAL_CFLAGS) \
	$(NULL)
ICalGLib_1_0_gir_SCANNERFLAGS = \
	--warn-all \
	$(NULL)
ICalGLib_1_0_gir_LIBS = \
	libical-glib-1.0.la \
	$(NULL)
ICalGLib_1_0_gir_FILES = \
	$(libical_glib_1_0_la_SOURCES) \
	$(privinclude_HEADERS) \
	$(NULL)

INTROSPECTION_GIRS += ICalGLib-1.0.gir

girdir = $(datadir)/gir-1.0
dist_gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES += $(dist_gir_DATA) $(typelib_DATA)
endif

@GNOME_CODE_COVERAGE_RULES@

EXTRA_DIST = \
	i-cal-object.c.in \
	i-cal-object.h.in \
	libical-glib.h.in \
	$(XML_FILES) \
	$(NULL)

CLEANFILES += $(BUILT_SOURCES)

-include $(top_srcdir)/git.mk
