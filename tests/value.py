#!/usr/bin/env python3
#GI_TYPELIB_PATH=$PREFIX/lib/girepository-1.0/ ./value.py

###############################################################################
#
# Copyright (C) 2015 William Yu <williamyu@gnome.org>
#
# This library is free software: you can redistribute it and/or modify it
# under the terms of version 2.1. of the GNU Lesser General Public License
# as published by the Free Software Foundation.
#
# This library is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
# for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library. If not, see <http://www.gnu.org/licenses/>.
#
###############################################################################

from gi.repository import ICalGLib

kind = ICalGLib.ValueKind.ATTACH_VALUE;
value = ICalGLib.Value.new (kind);
assert (value.is_valid() == 1);
assert (value.isa() == kind);
assert (value.isa_value() == 1);

string = "This is a link";
value_from_string = ICalGLib.Value.new_from_string (kind, string);
assert (value_from_string.as_ical_string_r() == string);
assert (value_from_string.is_valid() == 1);
assert (value_from_string.isa() == kind);
assert (value_from_string.isa_value() == 1);

value_from_string_clone = value_from_string.new_clone();
assert (value_from_string_clone.as_ical_string_r() == string);
assert (value_from_string_clone.is_valid() == 1);
assert (value_from_string_clone.isa() == kind);
assert (value_from_string_clone.isa_value() == 1);

value_a = ICalGLib.Value.new (ICalGLib.ValueKind.RECUR_VALUE);
value_b = ICalGLib.Value.new (ICalGLib.ValueKind.ATTACH_VALUE);
compare_result = ICalGLib.Value.compare (value_a, value_b);
assert (compare_result == ICalGLib.ParameterXliccomparetype.NOTEQUAL);

string_a = "a string";
string_b = "a string";
value_a = ICalGLib.Value.new_from_string (kind, string_a);
value_b = ICalGLib.Value.new_from_string (kind, string_b);
compare_result = ICalGLib.Value.compare (value_a, value_b);
assert (compare_result == ICalGLib.ParameterXliccomparetype.EQUAL);

string_a = "a string";
string_b = "b string";
value_a = ICalGLib.Value.new_from_string (kind, string_a);
value_b = ICalGLib.Value.new_from_string (kind, string_b);
compare_result = ICalGLib.Value.compare (value_a, value_b);
assert (compare_result == ICalGLib.ParameterXliccomparetype.NOTEQUAL);

kind_string = ICalGLib.Value.kind_to_string (kind);
assert (kind_string == "ATTACH");
converted_kind = ICalGLib.Value.string_to_kind (kind_string);
assert (converted_kind == kind);

szText = "This is a text\nand this is a new line";
after_encoded_szText = "This is a text\\nand this is a new line";
before_decoded_szText = "This is a text\\\nand this is a new line";
result = ICalGLib.Value.encode_ical_string (szText);
assert (result == after_encoded_szText);

result = ICalGLib.Value.decode_ical_string (before_decoded_szText);
assert (result == szText);