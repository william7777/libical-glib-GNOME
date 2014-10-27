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

by_second = recurrence.get_by_second();
assert len(by_second) == 61;
by_minute = recurrence.get_by_minute();
assert len(by_minute) == 61;
by_hour = recurrence.get_by_hour();
assert len(by_hour) == 25;
by_day = recurrence.get_by_day();
assert len(by_day) == 364;
by_month_day = recurrence.get_by_month_day();
assert len(by_month_day) == 32;
by_year_day = recurrence.get_by_year_day();
assert len(by_year_day) == 367;
by_week_no = recurrence.get_by_week_no();
assert len(by_week_no) == 54;
by_month = recurrence.get_by_month();
assert len(by_month) == 13;
by_set_pos = recurrence.get_by_set_pos();
assert len(by_set_pos) == 367;

recurrence.set_by_second(0, 1);
by_second = recurrence.get_by_second();
assert by_second[0] == 1;

recurrence = ICalGLib.RecurrenceType.from_string (string);

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
    