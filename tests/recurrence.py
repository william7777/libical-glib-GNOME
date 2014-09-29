#!/usr/bin/python3
#GI_TYPELIB_PATH=$PREFIX/lib/girepository-1.0/ ./recurrence-type.py

from gi.repository import ICalGLib

weekday = ICalGLib.RecurrenceType.day_day_of_week (0);
assert (weekday == ICalGLib.RecurrenceTypeWeekday.NO_WEEKDAY);
weekday = ICalGLib.RecurrenceType.day_day_of_week (1);
assert (weekday == ICalGLib.RecurrenceTypeWeekday.SUNDAY_WEEKDAY);

assert (ICalGLib.RecurrenceType.day_position(15) == 1);
assert (ICalGLib.RecurrenceType.day_position(16) == 2);
assert (ICalGLib.RecurrenceType.day_position(25) == 3);

string = "COUNT=10;FREQ=DAILY";
recurrence = ICalGLib.RecurrenceType.from_string (string);
assert (recurrence.as_string_r() == "FREQ=DAILY;COUNT=10");

assert (ICalGLib.recur_string_to_weekday ("MO") == ICalGLib.RecurrenceTypeWeekday.MONDAY_WEEKDAY);

start = 100000;
result = ICalGLib.recur_expand_recurrence (string, start, 10);
secs_per_day = 24*60*60;
for i in range (0, 9):
    assert (result[i] == start + i*secs_per_day);
    
    
string = "19970101T183248Z/19970102T071625Z";

period = ICalGLib.PeriodType.from_string (string);
start = period.get_start();
    
iter = ICalGLib.RecurIterator.new (recurrence, start);
timetype = iter.next();
day = timetype.get_day();
ref = 1;
while day != 0:
    assert (day == ref);
    ref += 1;
    timetype = iter.next();
    day = timetype.get_day();
    