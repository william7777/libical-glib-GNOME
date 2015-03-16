dnl libical-glib version
m4_define([ical_major_version], [1])
m4_define([ical_minor_version], [0])
m4_define([ical_micro_version], [1])

m4_define([ical_version], [ical_major_version.ical_minor_version.ical_micro_version])

AC_PREREQ(2.58)
AC_INIT([libical-glib], [ical_version], [http://bugzilla.gnome.org/browse.cgi?product=TODO])
AM_INIT_AUTOMAKE([gnu 1.9 dist-xz no-dist-gzip -Wno-portability tar-ustar])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR(README)
AC_CONFIG_HEADERS(config.h)

dnl *******************
dnl Required Packages
dnl *******************
m4_define([libical_minimum_version], [1.0])
m4_define([libxml_minimum_version], [2.7.3])

dnl Keep these two definitions in agreement.
m4_define([glib_minimum_version], [2.32])
m4_define([glib_encoded_version], [GLIB_VERSION_2_32])

dnl ***********************************
dnl Automake 1.11 - Silent Build Rules
dnl ***********************************
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

dnl ****************************
dnl Initialize maintainer mode
dnl ****************************
AM_MAINTAINER_MODE([enable])

if test "x$enable_maintainer_mode" = "xyes" ; then
	AC_DEFINE(ENABLE_MAINTAINER_MODE, 1, [Configured with enabled maintainer mode])
fi

AC_PROG_CC
AC_PROG_CPP
AC_C_INLINE
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

dnl ******************************
dnl Check for Win32
dnl ******************************

AC_MSG_CHECKING([for Win32])
case "$host" in
*-mingw*)
	os_win32=yes
	NO_UNDEFINED='-no-undefined'
	;;
*)
	os_win32=no
	NO_UNDEFINED='-no-undefined'
	;;
esac

AC_MSG_RESULT([$os_win32])
AM_CONDITIONAL(OS_WIN32, [test "x$os_win32" = "xyes"])
AC_SUBST(NO_UNDEFINED)

dnl ***********************
dnl Compiler Warning Flags
dnl ***********************

proposed_warning_flags=

if test "x$enable_maintainer_mode" = "xyes" ; then
	proposed_warning_flags="-Wall -Wextra -Wdeprecated-declarations"
else
	proposed_warning_flags="-Wno-deprecated-declarations"
fi

AS_COMPILER_FLAGS(WARNING_FLAGS,
	"$proposed_warning_flags
	-Wno-missing-field-initializers
	-Wno-sign-compare
	-Wno-unused-parameter
	-Wdeclaration-after-statement
	-Werror-implicit-function-declaration
	-Wformat-nonliteral -Wformat-security -Winit-self
	-Wmissing-declarations -Wmissing-include-dirs
	-Wmissing-noreturn -Wnested-externs -Wpointer-arith
	-Wundef -Wwrite-strings")
AC_SUBST(WARNING_FLAGS)

dnl Other useful compiler warnings for test builds only.
dnl These may produce warnings we have no control over.
dnl
dnl	-Wmissing-format-attribute
dnl	-Wshadow
dnl	-Wredundant-decls

CFLAGS="$CFLAGS $WARNING_FLAGS"

dnl Warn about API usage that violates our minimum requirements.
CFLAGS="$CFLAGS -DGLIB_VERSION_MAX_ALLOWED=glib_encoded_version"

dnl These will suppress warnings about newly-deprecated symbols.  Ideally
dnl these settings should match our minimum requirements and we will clean
dnl up any new deprecation warnings after bumping our minimum requirements.
dnl But if the warnings get to be overwhelming, use fixed versions instead.
CFLAGS="$CFLAGS -DGLIB_VERSION_MIN_REQUIRED=glib_encoded_version"

dnl ****************************
dnl Initialize libtool
dnl ****************************
AM_DISABLE_STATIC
AC_PROG_LIBTOOL

PKG_PROG_PKG_CONFIG

GNOME_CODE_COVERAGE

GOBJECT_INTROSPECTION_CHECK([0.9.12])

dnl ********************************
dnl Check for packages
dnl ********************************
PKG_CHECK_MODULES(GLIB,    [glib-2.0 >= glib_minimum_version])
PKG_CHECK_MODULES(LIBICAL, [libical >= libical_minimum_version])
PKG_CHECK_MODULES(LIBXML,  [libxml-2.0 >= libxml_minimum_version])
PKG_CHECK_MODULES(GOBJECT2, gobject-2.0)

dnl ******************************
dnl Gtk Doc stuff
dnl ******************************
# check for gtk-doc
m4_ifdef([GTK_DOC_CHECK], [
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])
],[
AM_CONDITIONAL([ENABLE_GTK_DOC], false)
])
AC_CONFIG_MACRO_DIR(m4)

dnl ******************************
dnl Special directories
dnl ******************************

privincludedir='${includedir}'/libical-glib
AC_SUBST(privincludedir)

dnl **************************
dnl Makefiles
dnl **************************
AC_CONFIG_FILES([
Makefile
libical-glib.pc
src/api/Makefile
src/Makefile
src/build-tools/Makefile
src/libical-glib/Makefile
tests/Makefile
docs/Makefile
docs/reference/Makefile
docs/reference/libical-glib/Makefile
])
AC_OUTPUT

AC_MSG_NOTICE([
	Introspection:		$enable_introspection
	Code coverage (gcov):	$enable_code_coverage
	Gtk-doc:		$enable_gtk_doc
])
