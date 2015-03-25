#!/usr/bin/env python3
#GI_TYPELIB_PATH=$PREFIX/lib/girepository-1.0/ ./array.py

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

import sys
from gi.repository import ICalGLib
from sys import getsizeof

array = ICalGLib.Array.new(100, 100);

element1 = "hello";
element2 = "world";
element3 = "how";
element4 = "are";
element5 = "you";

#TEST APPEND
array.append (element1);
array.append (element2);
array.append (element3);
array.append (element4);
array.append (element5);

e1 = array.element_at(0);
assert (element1 == e1);
e2 = array.element_at(1);
assert (element2 == e2);
e3 = array.element_at(2);
assert (element3 == e3);
e4 = array.element_at(3);
assert (element4 == e4);
e5 = array.element_at(4);
assert (element5 == e5);

#TEST COPY
clone = array.copy();
e1 = clone.element_at(0);
assert (element1 == e1);
e2 = clone.element_at(1);
assert (element2 == e2);
e3 = clone.element_at(2);
assert (element3 == e3);
e4 = clone.element_at(3);
assert (element4 == e4);
e5 = clone.element_at(4);
assert (element5 == e5);

#TEST REMOVE
array.remove_element_at (2);
e3 = array.element_at(2);
assert (element4 == e3);

attach1 = ICalGLib.Attach.new_from_url ("hello");
attach2 = ICalGLib.Attach.new_from_url ("world");
attach3 = ICalGLib.Attach.new_from_url ("how");
attach4 = ICalGLib.Attach.new_from_url ("are");
attach5 = ICalGLib.Attach.new_from_url ("you");

def my_cmp(a, b): 
    return cmp(a.get_url(), b.get_url());
   
array = ICalGLib.Array.new(10000, 10000);
array.append (attach1);
array.append (attach2);
array.append (attach3);

#TEST SORT
#ICalGLib.Array.sort (array, my_cmp);



