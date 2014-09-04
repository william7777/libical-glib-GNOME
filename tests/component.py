#!/usr/bin/python3
#GI_TYPELIB_PATH=$PREFIX/lib/girepository-1.0/ ./test-cal.py

from gi.repository import ICalGLib

event_str1 = \
    "BEGIN:VEVENT\n"                                \
    "UID:event-uid-123\n"                           \
    "SUMMARY;LANGUAGE=en-US:test1\n"                 \
    "DTSTART;TZID=Europe/Prague:20140306T090000\n"  \
    "DTEND;TZID=Europe/Berlin:20140306T093000\n"    \
    "CLASS:PUBLIC\n"                                \
    "PRIORITY:5\n"                                  \
    "DTSTAMP:20140207T020756Z\n"                    \
    "TRANSP:OPAQUE\n"                               \
    "STATUS:CONFIRMED\n"                            \
    "SEQUENCE:0\n"                                  \
    "LOCATION;LANGUAGE=en-US:Location\n"            \
    "END:VEVENT\n"

event_str2 = \
    "BEGIN:VEVENT\n"                                \
    "UID:event-uid-123\n"                           \
    "SUMMARY;LANGUAGE=en-US:test2\n"                 \
    "DTSTART;TZID=Europe/Prague:20140306T090000\n"  \
    "DTEND;TZID=Europe/Berlin:20140306T093000\n"    \
    "CLASS:PUBLIC\n"                                \
    "PRIORITY:5\n"                                  \
    "DTSTAMP:20140207T020756Z\n"                    \
    "TRANSP:OPAQUE\n"                               \
    "STATUS:CONFIRMED\n"                            \
    "SEQUENCE:0\n"                                  \
    "LOCATION;LANGUAGE=en-US:Location\n"            \
    "END:VEVENT\n"

event_str3 = \
    "BEGIN:VEVENT\n"                                \
    "UID:event-uid-123\n"                           \
    "SUMMARY;LANGUAGE=en-US:test3\n"                 \
    "DTSTART;TZID=Europe/Prague:20140306T090000\n"  \
    "DTEND;TZID=Europe/Berlin:20140306T093000\n"    \
    "CLASS:PUBLIC\n"                                \
    "PRIORITY:5\n"                                  \
    "DTSTAMP:20140207T020756Z\n"                    \
    "TRANSP:OPAQUE\n"                               \
    "STATUS:CONFIRMED\n"                            \
    "SEQUENCE:0\n"                                  \
    "LOCATION;LANGUAGE=en-US:Location\n"            \
    "END:VEVENT\n"

event_str4 = \
    "BEGIN:VCALENDAR\n"                                \
    "UID:event-uid-123\n"                           \
    "SUMMARY;LANGUAGE=en-US:test4\n"                 \
    "DTSTART;TZID=Europe/Prague:20140306T090000\n"  \
    "DTEND;TZID=Europe/Berlin:20140306T093000\n"    \
    "CLASS:PUBLIC\n"                                \
    "PRIORITY:5\n"                                  \
    "DTSTAMP:20140207T020756Z\n"                    \
    "TRANSP:OPAQUE\n"                               \
    "STATUS:CONFIRMED\n"                            \
    "SEQUENCE:0\n"                                  \
    "LOCATION;LANGUAGE=en-US:Location\n"            \
    "END:VCALENDAR\n"

event_str5 = \
    "BEGIN:VCALENDAR\n"                                \
    "UID:event-uid-123\n"                           \
    "SUMMARY;LANGUAGE=en-US:test5\n"                 \
    "DTSTART;TZID=Europe/Prague:20140306T090000\n"  \
    "DTEND;TZID=Europe/Berlin:20140306T093000\n"    \
    "CLASS:PUBLIC\n"                                \
    "PRIORITY:5\n"                                  \
    "DTSTAMP:20140207T020756Z\n"                    \
    "TRANSP:OPAQUE\n"                               \
    "STATUS:CONFIRMED\n"                            \
    "SEQUENCE:0\n"                                  \
    "LOCATION;LANGUAGE=en-US:Location\n"            \
    "END:VCALENDAR\n"

def main ():
	#Test as_ical_string_r
	comp = ICalGLib.Component.new_from_string (event_str1);
	string = comp.as_ical_string_r ();

	#Test new_clone
	clone = comp.new_clone();
	string1 = clone.as_ical_string_r ();
	assert (string == string1);

	#Test check_restrictions
	assert (comp.check_restrictions() == 0);

	#Test count_errors
	assert (comp.count_errors() == 0);

	#Test kind_is_valid
	assert (ICalGLib.Component.kind_is_valid (ICalGLib.ComponentKind.VEVENT_COMPONENT) == True);
	
	#Test string_to_kind and kind_to_string
	kind = ICalGLib.Component.string_to_kind ("VEVENT");
	string = ICalGLib.Component.kind_to_string (kind);
	assert (string == "VEVENT");

	#Test set_summary/get_summary
	assert (comp.get_summary () == "test1");
	comp.set_summary ("newSummary");
	assert (comp.get_summary () == "newSummary");

	#Test set_comment/get_comment
	assert (comp.get_comment () == None);
	comp.set_comment ("newcomment");
	assert (comp.get_comment () == "newcomment");

	#Test set_uid/get_uid
	assert (comp.get_uid () == "event-uid-123");
	comp.set_uid ("newuid");
	assert (comp.get_uid () == "newuid");

	#Test set_relcalid/get_relcalid
	assert (comp.get_relcalid () == None);
	comp.set_relcalid ("newrelcalid");
	assert (comp.get_relcalid () == "newrelcalid");

	#Test set_description/get_description
	assert (comp.get_description () == None);
	comp.set_description ("newdescription");
	assert (comp.get_description () == "newdescription");

	#Test set_location/get_location
	assert (comp.get_location () == "Location");
	comp.set_location ("newlocation");
	assert (comp.get_location () == "newlocation");

	#Test set_sequence/get_sequence
	assert (comp.get_sequence () == 0);
	comp.set_sequence (5);
	assert (comp.get_sequence () == 5);


	#Test add_component
	parent = ICalGLib.Component.new_from_string (event_str1);
	comp1 = ICalGLib.Component.new_from_string (event_str1);
	comp2 = ICalGLib.Component.new_from_string (event_str2);
	comp3 = ICalGLib.Component.new_from_string (event_str3);
	comp4 = ICalGLib.Component.new_from_string (event_str4);
	comp5 = ICalGLib.Component.new_from_string (event_str5);

	parent.add_component (comp1);
	parent.add_component (comp2);
	parent.add_component (comp3);
	parent.add_component (comp4);
	parent.add_component (comp5);

	real = parent.get_first_real_component();
	comp1_string = comp1.as_ical_string_r ();
	real_string = real.as_ical_string_r ();
	assert (comp1_string == real_string);

	#Test count_components
	assert (parent.count_components(ICalGLib.ComponentKind.VEVENT_COMPONENT) == 3);

	#Test get_first_component and get_next_component
	comp = parent.get_first_component (ICalGLib.ComponentKind.VEVENT_COMPONENT);

	#Test get_dtstart and get_dtend
	comp = parent.get_first_component (ICalGLib.ComponentKind.VEVENT_COMPONENT);
	dtstart = comp.get_dtstart ();
	start_string = ICalGLib.time_as_ical_string_r (dtstart);
	assert (start_string == "20140306T090000");
	dtend = comp.get_dtend();
	end_string = ICalGLib.time_as_ical_string_r (dtend);
	assert (end_string == "20140306T093000");
	
	#Test merge_component
	comp4_string = comp4.as_ical_string_r();
	comp4.merge_component (comp5);
	assert (comp4.as_ical_string_r() == comp4_string);
	assert (comp5.as_ical_string_r() == None);

	

if __name__=="__main__":
    main ()
