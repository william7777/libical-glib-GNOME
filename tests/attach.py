#!/usr/bin/env python3
#GI_TYPELIB_PATH=$PREFIX/lib/girepository-1.0/ ./attach.py

from gi.repository import ICalGLib

dummy_url = "https://people.gnome.org/~engagement/logos/GnomeLogoVertical.svg";
dummy_data = "It's a super large attachment";

attach_url = ICalGLib.Attach.new_from_url (dummy_url);
assert (attach_url.get_is_url() == 1);

retrieved_url = attach_url.get_url();
assert (retrieved_url == dummy_url);

attach_data = ICalGLib.Attach.new_from_data (dummy_data, ICalGLib.memory_free_buffer, None);
assert (attach_data.get_is_url() == 0);
retrieved_data = attach_data.get_data();
assert (retrieved_data == dummy_data);