NULL =

# The name of the module.
DOC_MODULE = libical-glib

# The top-level SGML file.
DOC_MAIN_SGML_FILE = $(DOC_MODULE)-docs.sgml

# The directory containing the source code (if it contains documentation).
DOC_SOURCE_DIR = $(top_srcdir)/src/libical-glib

HTML_DIR = $(datadir)/gtk-doc/html

# Extra options to supply to gtkdoc-scan
SCAN_OPTIONS = --rebuild-types --deprecated-guards="LIBICAL_GLIB_DISABLE_DEPRECATED"

# Extra options to pass to gtkdoc-scangobj
SCANGOBJ_OPTIONS =

# Extra options to supply to gtkdoc-mkdb
MKDB_OPTIONS = --sgml-mode --output-format=xml --name-space=i-cal


# CFLAGS and LDFLAGS for compiling gtkdoc-scangobj with your library.
GTKDOC_CFLAGS = \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/src/libical-glib \
	-I$(top_builddir)/src \
	-I$(top_builddir)/src/libical-glib \
	$(GLIB_CFLAGS) \
	$(GOBJECT2_CFLAGS) \
	$(LIBICAL_CFLAGS) \
	$(NULL)

GTKDOC_LIBS = \
	$(top_builddir)/src/libical-glib/libical-glib-1.0.la \
	$(GLIB_LIBS) \
	$(LIBICAL_LIBS) \
	$(GOBJECT2_LIBS) \
	$(NULL)

# Extra SGML files that are included by $(DOC_MAIN_SGML_FILE)
content_files = 

# Used for dependencies. The docs will be rebuilt if any of these change.
HFILE_GLOB=$(top_srcdir)/src/libical-glib/*.h
CFILE_GLOB=$(top_srcdir)/src/libical-glib/*.c

# Header files to ignore when scanning
# XXX Ignore the imapx provider for now.
IGNORE_HFILES = 

# This includes the standard gtk-doc make rules, copied by gtkdocize.
include $(top_srcdir)/gtk-doc.make

# Other files to distribute
EXTRA_DIST += \
	$(content_files) \
	$(DOC_MODULE)-docs.sgml \
	$(DOC_MODULE)-sections.txt \
	$(NULL)

#TESTS = $(GTKDOC_CHECK)

-include $(top_srcdir)/git.mk