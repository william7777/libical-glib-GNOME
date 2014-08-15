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
	print ("Event: %s" % string);

	#Test new_clone
	clone = comp.new_clone();
	string = clone.as_ical_string_r ();
	print ("Clone: %s" % string);

	#Test check_restrictions
	print ("There are %d restrictions" % comp.check_restrictions());

	#Test count_errors
	print ("There are %d errors" % comp.count_errors());

	#Test kind_is_valid
	print ("Is the kind valid? %d\n" % ICalGLib.Component.kind_is_valid (ICalGLib.ComponentKind.VEVENT_COMPONENT));
	
	#Test string_to_kind and kind_to_string
	kind = ICalGLib.Component.string_to_kind ("VEVENT");
	string = ICalGLib.Component.kind_to_string (kind);
	print ("The kind is %s" % string);

	#Test set_summary/get_summary
	print ("The summary of comp is %s" % comp.get_summary ());
	comp.set_summary ("newSummary");
	print ("The new summary of comp is %s" % comp.get_summary ());

	#Test set_comment/get_comment
	print ("The comment of comp is %s" % comp.get_comment ());
	comp.set_comment ("newcomment");
	print ("The new comment of comp is %s" % comp.get_comment ());

	#Test set_uid/get_uid
	print ("The uid of comp is %s" % comp.get_uid ());
	comp.set_uid ("newuid");
	print ("The new uid of comp is %s" % comp.get_uid ());

	#Test set_relcalid/get_relcalid
	print ("The relcalid of comp is %s" % comp.get_relcalid ());
	comp.set_relcalid ("newrelcalid");
	print ("The new relcalid of comp is %s" % comp.get_relcalid ());

	#Test set_description/get_description
	print ("The description of comp is %s" % comp.get_description ());
	comp.set_description ("newdescription");
	print ("The new description of comp is %s" % comp.get_description ());

	#Test set_location/get_location
	print ("The location of comp is %s" % comp.get_location ());
	comp.set_location ("newlocation");
	print ("The new location of comp is %s" % comp.get_location ());

	#Test set_sequence/get_sequence
	print ("The sequence of comp is %s" % comp.get_sequence ());
	comp.set_sequence (5);
	print ("The new sequence of comp is %d" % comp.get_sequence ());


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
	real_string = real.as_ical_string_r ();
	print ("The real is %s\n" % real_string);

	#Test count_components
	print ("There are %d components\n" % parent.count_components(ICalGLib.ComponentKind.VEVENT_COMPONENT));

	#Test get_first_component and get_next_component
	comp = parent.get_first_component (ICalGLib.ComponentKind.VEVENT_COMPONENT);
	while comp is not None:
		child_string = comp.as_ical_string_r();
		print ("The child is \n%s\n\n" % child_string);
		comp = parent.get_next_component (ICalGLib.ComponentKind.VEVENT_COMPONENT);

	#Test get_dtstart and get_dtend
	comp = parent.get_first_component (ICalGLib.ComponentKind.VEVENT_COMPONENT);
	dtstart = comp.get_dtstart ();
	start_string = dtstart.as_ical_string_r();
	print ("The start is %s\n", start_string);
	dtend = comp.get_dtend();
	end_string = dtend.as_ical_string_r();
	print ("The dtend is %s\n", end_string);
	
	#Test merge_component
	comp4 = ICalGLib.Component.new_from_string (event_str4);
	print ("The comp4 is \n%s\n" % comp4.as_ical_string_r());
	comp5 = ICalGLib.Component.new_from_string (event_str5);
	print ("The comp5 is \n%s\n" % comp5.as_ical_string_r());
	comp4.merge_component (comp5);
	print ("After merge:\n\n");
	print ("The comp4 is \n%s\n" % comp4.as_ical_string_r());
	print ("The comp5 is \n%s\n" % comp5.as_ical_string_r());

	

if __name__=="__main__":
    main ()
