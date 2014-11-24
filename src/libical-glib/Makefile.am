NULL =
CLEANFILES=
BUILT_SOURCES=

i-cal-object.c: i-cal-object.c.in
	cp $< $@

i-cal-object.h: i-cal-object.h.in
	cp $< $@
	
all_file_names = \
	i-cal-array \
	i-cal-attach \
	i-cal-comp-iter \
	i-cal-component \
	i-cal-datetimeperiod-type \
	i-cal-derived-parameter \
	i-cal-derived-property \
	i-cal-derived-value \
	i-cal-duration-type \
	i-cal-enums \
	i-cal-error \
	i-cal-geo-type \
	i-cal-langbind \
	i-cal-memory \
	i-cal-mime \
	i-cal-parameter \
	i-cal-parser \
	i-cal-period-type \
	i-cal-property \
	i-cal-recur \
	i-cal-recur-iterator \
	i-cal-recurrence-type \
	i-cal-reqstat-type \
	i-cal-restriction \
	i-cal-time \
	i-cal-time-span \
	i-cal-timetype \
	i-cal-timezone \
	i-cal-timezone-phase \
	i-cal-timezonetype \
	i-cal-trigger-type \
	i-cal-unknowntokenhandling \
	i-cal-value \
	$(NULL)
	
$(addsuffix .h, $(all_file_names)) $(addsuffix .c, $(all_file_names)): $(addprefix $(top_srcdir)/src/api/, $(addsuffix .xml, $(all_file_names)))
	$(top_builddir)/src/build-tools/src-generator "$(top_builddir)/src/build-tools" "$(top_builddir)/src/api" $(addsuffix .xml, $(all_file_names))

lib_LTLIBRARIES = libical-glib-1.0.la

libical_glib_1_0_la_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	-I$(top_srcdir)/src \
	-I$(top_builddir)/src \
	-DG_LOG_DOMAIN=\"libical-glib\" \
	-DLIBICAL_GLIB_COMPILATION \
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
	i-cal-array.c \
	i-cal-attach.c \
	i-cal-comp-iter.c \
	i-cal-component.c \
	i-cal-datetimeperiod-type.c \
	i-cal-derived-parameter.c \
	i-cal-derived-property.c \
	i-cal-derived-value.c \
	i-cal-duration-type.c \
	i-cal-enums.c \
	i-cal-error.c \
	i-cal-geo-type.c \
	i-cal-langbind.c \
	i-cal-memory.c \
	i-cal-mime.c \
	i-cal-parameter.c \
	i-cal-parser.c \
	i-cal-period-type.c \
	i-cal-property.c \
	i-cal-recur.c \
	i-cal-recur-iterator.c \
	i-cal-recurrence-type.c \
	i-cal-reqstat-type.c \
	i-cal-restriction.c \
	i-cal-time.c \
	i-cal-time-span.c \
	i-cal-timetype.c \
	i-cal-timezone.c \
	i-cal-timezone-phase.c \
	i-cal-timezonetype.c \
	i-cal-trigger-type.c \
	i-cal-unknowntokenhandling.c \
	i-cal-value.c \
	$(NULL)

privinclude_HEADERS = \
	libical-glib.h \
	i-cal-object.h \
	$(addsuffix .h, $(all_file_names)) \
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
	-DLIBICAL_GLIB_COMPILATION \
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
