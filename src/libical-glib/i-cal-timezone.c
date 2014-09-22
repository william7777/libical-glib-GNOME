/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * This library is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "i-cal-timezone.h"
#include "i-cal-component.h"


G_DEFINE_TYPE (ICalTimezone, i_cal_timezone, I_CAL_TYPE_OBJECT)

static void
i_cal_timezone_class_init (ICalTimezoneClass *klass)
{	
	g_type_class_add_private (klass, sizeof (ICalTimezone));
}

static void
i_cal_timezone_init (ICalTimezone *self)
{
}

/**
 * i_cal_timezone_new_full: (skip)
 **/
ICalTimezone *
i_cal_timezone_new_full (icaltimezone *native, 
                         GObject *owner, 
                         gboolean is_global_memory)
{
	ICalTimezone *object;
	object = g_object_new (I_CAL_TIMEZONE_TYPE, NULL);
	i_cal_object_construct ((ICalObject *)object,
		        	(gpointer) native,
		        	(GDestroyNotify) i_cal_timezone_destroy,
		        	is_global_memory,
		        	owner);
    							
	return object;
}

/**
 * i_cal_timezone_get_native_set_owner: (skip)
 **/
icaltimezone *
i_cal_timezone_get_native_set_owner (const ICalTimezone *object, 
                                     GObject *owner)
{
	icaltimezone *native_pointer;	
	if (owner != NULL)
		i_cal_object_set_owner ((ICalObject *)object, owner);
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	return native_pointer;
}

/**
 * i_cal_timezone_get_native_remove_owner: (skip)
 **/
icaltimezone *
i_cal_timezone_get_native_remove_owner (ICalTimezone *object)
{
	icaltimezone *native_pointer;	
	i_cal_object_remove_owner ((ICalObject *)object);
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	return native_pointer;
}

/**
 * i_cal_timezone_steal_native: (skip)
 **/
icaltimezone *
i_cal_timezone_steal_native (ICalTimezone *object)
{
	icaltimezone *native_pointer;
	native_pointer = (icaltimezone *)i_cal_object_steal_native ((ICalObject *)object);
    
	return native_pointer;
}

/**
 * i_cal_timezone_new:
 *
 * Returns: (transfer full) (allow-none): The newly created object of the type #ICalTimezone.
 *
 * The constructor of the type #ICalTimezone
 *
 * Since: 1.0
 *
 **/
ICalTimezone *
i_cal_timezone_new (void)
{
	return i_cal_timezone_new_full (icaltimezone_new (), NULL, FALSE) ;
}

/**
 * i_cal_timezone_destroy: (skip)
 * @zone: The #ICalTimezone to be freed
 *
 * The destructor of the type #ICalTimezone
 *
 * Since: 1.0
 *
 **/
void
i_cal_timezone_destroy (icaltimezone *zone)
{
	icaltimezone_free (zone, 1);
}

/**
 * i_cal_timezone_copy:
 * @zone: The #ICalTimezone needs to be cloned.
 *
 * Returns: (transfer none): The newly created #ICalTimezone with the same values as @zone
 *
 * The clone method for #ICalTimezone
 *
 * Since: 1.0
 *
 **/
ICalTimezone *
i_cal_timezone_copy (const ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), NULL);
	g_return_val_if_fail (zone != NULL, NULL);

	return i_cal_timezone_new_full (icaltimezone_copy (i_cal_timezone_get_native_set_owner (zone, NULL)), NULL, FALSE) ;
}

/**
 * i_cal_timezone_free:
 * @zone: The #ICalTimezone to be freed
 * @free_struct: Whether to free it or reset it. 1 to free and 0 to reset
 *
 * The destructor of #ICalTimezone
 *
 * Since: 1.0
 *
 **/
void
i_cal_timezone_free (ICalTimezone *zone, 
                     gint free_struct)
{
	g_return_if_fail (I_CAL_IS_TIMEZONE (zone));
	g_return_if_fail (zone != NULL);

	icaltimezone_free (i_cal_timezone_get_native_set_owner (zone, NULL), free_struct);
}

/**
 * i_cal_timezone_set_tzid_prefix:
 * @new_prefix: The #ICalTimezone to be set
 *
 * Sets the prefix to be used for tzid's generated from system tzdata. Must be globally unique (such as
 * a domain name owned by the developer of the calling application), and begin and end with forward slashes.
 * Do not change or de-allocate the string buffer after calling this.
 *
 * Since: 1.0
 *
 **/
void
i_cal_timezone_set_tzid_prefix (const gchar *new_prefix)
{
	g_return_if_fail (new_prefix != NULL);

	icaltimezone_set_tzid_prefix (new_prefix);
}

/**
 * i_cal_timezone_free_builtin_timezones:
 *
 * Free any builtin timezone information
 *
 * Since: 1.0
 *
 **/
void
i_cal_timezone_free_builtin_timezones (void)
{
	icaltimezone_free_builtin_timezones ();
}

/**
 * i_cal_timezone_get_builtin_timezone:
 * @location: The location representing the timezone.
 *
 * Returns: (transfer full): The builtin #ICalTimezone with the name of @location
 *
 * Returns a single builtin timezone, given its Olson city name.
 *
 * Since: 1.0
 *
 **/
ICalTimezone *
i_cal_timezone_get_builtin_timezone (const gchar *location)
{
	g_return_val_if_fail (location != NULL, NULL);

	return i_cal_timezone_new_full (icaltimezone_get_builtin_timezone (location), NULL, FALSE) ;
}

/**
 * i_cal_timezone_get_builtin_timezone_from_offset:
 * @offset: The offset used to get the #ICalTimezone
 * @tzname: The reference #ICalTimezone name
 *
 * Returns: (transfer full)
 *
 * Returns a single builtin timezone, given its offset.
 *
 * Since: 1.0
 *
 **/
ICalTimezone *
i_cal_timezone_get_builtin_timezone_from_offset (gint offset, 
                                                 const gchar *tzname)
{
	g_return_val_if_fail (tzname != NULL, NULL);

	return i_cal_timezone_new_full (icaltimezone_get_builtin_timezone_from_offset (offset, tzname), NULL, FALSE) ;
}

/**
 * i_cal_timezone_get_builtin_timezone_from_tzid:
 * @tzid: The tzid name
 *
 * Returns: (transfer full)
 *
 * Returns a single builtin timezone, given its TZID.
 *
 * Since: 1.0
 *
 **/
ICalTimezone *
i_cal_timezone_get_builtin_timezone_from_tzid (const gchar *tzid)
{
	g_return_val_if_fail (tzid != NULL, NULL);

	return i_cal_timezone_new_full (icaltimezone_get_builtin_timezone_from_tzid (tzid), NULL, FALSE) ;
}

/**
 * i_cal_timezone_get_utc_timezone:
 *
 * Returns: (transfer full): The utc #ICalTimezone
 *
 * Returns the UTC timezone.
 *
 * Since: 1.0
 *
 **/
ICalTimezone *
i_cal_timezone_get_utc_timezone (void)
{
	return i_cal_timezone_new_full (icaltimezone_get_utc_timezone (), NULL, FALSE) ;
}

/**
 * i_cal_timezone_get_tzid:
 * @zone: The #ICalTimezone to be queried
 *
 * Returns: The timezone id
 *
 * Returns the TZID of a timezone.
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_timezone_get_tzid (const ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), NULL);
	g_return_val_if_fail (zone != NULL, NULL);

	return icaltimezone_get_tzid (i_cal_timezone_get_native_set_owner (zone, NULL));
}

/**
 * i_cal_timezone_get_location:
 * @zone: The #ICalTimezone to be queried
 *
 * Returns: The location of the #ICalTimezone
 *
 * Returns the city name of a timezone.
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_timezone_get_location (const ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), NULL);
	g_return_val_if_fail (zone != NULL, NULL);

	return icaltimezone_get_location (i_cal_timezone_get_native_set_owner (zone, NULL));
}

/**
 * i_cal_timezone_get_tznames:
 * @zone: The #ICalTimezone to be queried
 *
 * Returns: The timezone name
 *
 * Returns the TZNAME properties used in the latest STANDARD and DAYLIGHT components. If they are the same
 * it will return just one, e.g. "LMT". If they are different it will format them like "EST/EDT". Note that
 * this may also return NULL.
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_timezone_get_tznames (const ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), NULL);
	g_return_val_if_fail (zone != NULL, NULL);

	return icaltimezone_get_tznames (i_cal_timezone_get_native_set_owner (zone, NULL));
}

/**
 * i_cal_timezone_get_latitude:
 * @zone: The #ICalTimezone to be queried
 *
 * Returns: The latitude of the #ICalTimezone
 *
 * Returns the latitude of a builtin timezone.
 *
 * Since: 1.0
 *
 **/
gdouble
i_cal_timezone_get_latitude (const ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), 0);
	g_return_val_if_fail (zone != NULL, 0);

	return icaltimezone_get_latitude (i_cal_timezone_get_native_set_owner (zone, NULL));
}

/**
 * i_cal_timezone_get_longitude:
 * @zone: The #ICalTimezone to be queried
 *
 * Returns: The longitude of the #ICalTimezone.
 *
 * Returns the longitude of a builtin timezone.
 *
 * Since: 1.0
 *
 **/
gdouble
i_cal_timezone_get_longitude (const ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), 0);
	g_return_val_if_fail (zone != NULL, 0);

	return icaltimezone_get_longitude (i_cal_timezone_get_native_set_owner (zone, NULL));
}

/**
 * i_cal_timezone_get_component:
 * @zone: The #ICalTimezone to be queried
 *
 * Returns: (transfer full): the VTIMEZONE component of the @zone.
 *
 * Returns the VTIMEZONE component of a timezone.
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_timezone_get_component (const ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), NULL);
	g_return_val_if_fail (zone != NULL, NULL);

	return i_cal_component_new_full (icaltimezone_get_component (i_cal_timezone_get_native_set_owner (zone, NULL)), (GObject *)zone) ;
}

/**
 * i_cal_timezone_set_component:
 * @zone: The #ICalTimezone to be set
 * @comp: The VTIMEZONE component of an #ICalTimezone, initializing the tzid, location and tzname fields.
 *
 * Returns: Whether the action is successful. 1 for success, 0 for failure.
 *
 * Sets the VTIMEZONE component of #ICalTimezone, initializing the tzid, location and tzname fields. It
 * returns 1 on success or 0 on failure, i.e. no TZID was found.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_timezone_set_component (ICalTimezone *zone, 
                              ICalComponent *comp)
{
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), 0);
	g_return_val_if_fail (zone != NULL, 0);
	g_return_val_if_fail (I_CAL_IS_COMPONENT (comp), 0);
	g_return_val_if_fail (comp != NULL, 0);

	return icaltimezone_set_component (i_cal_timezone_get_native_set_owner (zone, NULL), i_cal_component_get_native_set_owner (comp, NULL));
}

/**
 * i_cal_timezone_get_display_name:
 * @zone: The #ICalTimezone to be queried
 *
 * Returns: The display name of @zone
 *
 * Get the display name of the @zone.
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_timezone_get_display_name (const ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), NULL);
	g_return_val_if_fail (zone != NULL, NULL);

	return icaltimezone_get_display_name (i_cal_timezone_get_native_set_owner (zone, NULL));
}

/**
 * i_cal_timezone_release_zone_tab:
 *
 * Free memory dedicated to the zonefile directory
 *
 * Since: 1.0
 *
 **/
void
i_cal_timezone_release_zone_tab (void)
{
	icaltimezone_release_zone_tab ();
}


