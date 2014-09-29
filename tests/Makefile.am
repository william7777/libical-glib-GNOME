NULL =

@GNOME_CODE_COVERAGE_RULES@

TESTS =  \
	component.py \
	array.py \
	attach.py \
	duration-type.py \
	error.py \
	parameter.py \
	value.py \
	period-type.py \
	$(NULL)

TESTS_ENVIRONMENT = . $(abs_top_srcdir)/tests/tests-env.sh "$(abs_top_builddir)/src/libical-glib/" "$(abs_top_builddir)/src/libical-glib/.libs/";

-include $(top_srcdir)/git.mk
