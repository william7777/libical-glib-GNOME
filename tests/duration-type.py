#!/usr/bin/env python3
#GI_TYPELIB_PATH=$PREFIX/lib/girepository-1.0/ ./duration-type.py

from gi.repository import ICalGLib

length = 1000000000;
bad_string = "This is a bad string";

duration = ICalGLib.DurationType.from_int (length);
assert (duration.as_int() == length);
length_in_string = duration.as_ical_string_r();
duration1 = ICalGLib.DurationType.from_string (length_in_string);
assert (duration1.as_ical_string_r() == length_in_string);
assert (length == duration1.as_int());

duration = ICalGLib.DurationType.from_string(bad_string);
duration_bad = ICalGLib.DurationType.bad_duration();
assert (duration.as_ical_string_r() == duration_bad.as_ical_string_r());
assert (duration.is_bad_duration() == 1);
duration_null = ICalGLib.DurationType.null_duration();
assert (duration_null.is_null_duration() == 1);