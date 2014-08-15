NULL =

noinst_PROGRAMS = src-generator

src_generator_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	$(GLIB_CFLAGS) \
	$(LIBXML_CFLAGS) \
	-DG_LOG_DOMAIN=\"src-generator\" \
	$(NULL)

src_generator_SOURCES = \
	common-header.h \
	generator.c \
	generator.h \
	xml-parser.c \
	xml-parser.h \
	$(NULL)

src_generator_LDADD = \
	$(GLIB_LIBS) \
	$(LIBXML_LIBS) \
	$(NULL)

EXTRA_DIST = \
	header-structure-boilerplate-template \
	header-template \
	source-structure-boilerplate-template \
	source-template \
	$(NULL)

-include $(top_srcdir)/git.mk
