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
	property.py \
	recurrence-type.py \
	timezone.py \
	comprehensive.py \
	$(NULL)

TESTS_ENVIRONMENT = . $(abs_top_srcdir)/tests/tests-env.sh "$(abs_top_builddir)/src/libical-glib/" "$(abs_top_builddir)/src/libical-glib/.libs/";

EXTRA_DIST = \
	component.py \
	array.py \
	attach.py \
	duration-type.py \
	error.py \
	parameter.py \
	value.py \
	period-type.py \
	property.py \
	recurrence-type.py \
	timezone.py \
	comprehensive.py \
	tests-env.sh \
	$(NULL)

-include $(top_srcdir)/git.mk
