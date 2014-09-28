#!/usr/bin/python3
#GI_TYPELIB_PATH=$PREFIX/lib/girepository-1.0/ ./parameter.py

from gi.repository import ICalGLib

# Test interaction with gchar
altrep = "This is an altrep";
parameter = ICalGLib.Parameter.new_altrep (altrep);
retrieved_altrep = parameter.get_altrep();
assert (retrieved_altrep == altrep);
another_altrep = "This is an another altrep";
parameter.set_altrep(another_altrep);
retrieved_altrep = parameter.get_altrep();
assert (retrieved_altrep == another_altrep);

# Test interaction with enum
action = ICalGLib.ParameterAction.X;
parameter = ICalGLib.Parameter.new_actionparam (action);
retrieved_action = parameter.get_actionparam ();
assert (retrieved_action == action);
action = ICalGLib.ParameterAction.ASK;
parameter.set_actionparam (action);
retrieved_action = parameter.get_actionparam ();
assert (retrieved_action == action);

# Test general utilities
kind = ICalGLib.ParameterKind.ACTIONPARAM_PARAMETER;
parameter = ICalGLib.Parameter.new(kind);
assert (parameter.isa() == kind);
assert (parameter.isa_parameter() == 1);
string = parameter.as_ical_string_r();
assert (string == None);
clone = parameter.new_clone ();
assert (clone.isa() == kind);
assert (clone.isa_parameter() == 1);
string = clone.as_ical_string_r();
assert (string == None);

string = ICalGLib.Parameter.kind_to_string (kind);
assert (string == "ACTIONPARAM");
assert (ICalGLib.Parameter.string_to_kind (string) == kind);

value = "This is a value";
typevalue = string + "=" + value;
parameter = ICalGLib.Parameter.new_from_string (typevalue);
assert (parameter.as_ical_string_r() == typevalue);
assert (parameter.isa() == kind);
assert (parameter.isa_parameter() == 1);


another_parameter = ICalGLib.Parameter.new_from_value_string (kind, value);
assert (another_parameter.as_ical_string_r() == typevalue);