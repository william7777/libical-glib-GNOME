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

#include "i-cal-timetype.h"
#include "i-cal-timezone.h"


G_DEFINE_TYPE (ICalTimetype, i_cal_timetype, I_CAL_TYPE_OBJECT)

static void
i_cal_timetype_class_init (ICalTimetypeClass *klass)
{	
	g_type_class_add_private (klass, sizeof (ICalTimetype));
}

static void
i_cal_timetype_init (ICalTimetype *self)
{
}

/**
 * i_cal_timetype_new_full: (skip)
 **/
ICalTimetype *
i_cal_timetype_new_full (icaltimetype native)
{
	ICalTimetype *object;
	icaltimetype *clone;
	object = g_object_new (I_CAL_TIMETYPE_TYPE, NULL);
	clone = g_new (icaltimetype, 1);
	*clone = native;
	i_cal_object_construct ((ICalObject *)object,
		        	(gpointer) clone,
		        	(GDestroyNotify) g_free,
		        	FALSE,
		        	NULL);
    							
	return object;
}

/**
 * i_cal_timetype_get_native_set_owner: (skip)
 **/
icaltimetype
i_cal_timetype_get_native_set_owner (const ICalTimetype *object)
{
	icaltimetype *native_pointer;
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	
	if (native_pointer) {
		return *native_pointer;
	} else {
		return i_cal_timetype_new();
	}
}

/**
 * i_cal_timetype_get_native_pointer_set_owner: (skip)
 **/
icaltimetype *
i_cal_timetype_get_native_pointer_set_owner (ICalTimetype *object)
{
	return i_cal_object_get_native ((ICalObject *)object);
}

/**
 * i_cal_timetype_get_native_remove_owner: (skip)
 **/
icaltimetype 
i_cal_timetype_get_native_remove_owner (ICalTimetype *object)
{
	icaltimetype *native_pointer;	
	i_cal_object_remove_owner ((ICalObject *)object);
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	
	if (native_pointer) {
		return *native_pointer;
	} else {
		return i_cal_timetype_new();
	}
}

/**
 * i_cal_timetype_steal_native: (skip)
 **/
icaltimetype 
i_cal_timetype_steal_native (ICalTimetype *object)
{
	icaltimetype *native_pointer;
	icaltimetype native;
	native_pointer = (icaltimetype *)i_cal_object_steal_native ((ICalObject *)object);
    
	if (native_pointer != NULL) {
		native = *native_pointer;
		g_free (native_pointer);
		return native;
	} else {
		return i_cal_timetype_new();
	}
}

/**
 * i_cal_timetype_new: (skip)
 *
 * Returns: The newly created #ICalTimetype. It is the epoch time (19700-1-1 00:00:00 utc)
 *
 * Create a new #ICalTimetype.
 *
 * Since: 1.0
 *
 **/
icaltimetype
i_cal_timetype_new (void)
{
	icaltimetype timetype;
	timetype.year = 1970;
	timetype.month = 1;
	timetype.day = 1;
	timetype.hour = 0;
	timetype.minute = 0;
	timetype.second = 0;
	timetype.is_utc = 1;
	timetype.is_date = 0;
	timetype.is_daylight = 0;
	timetype.zone = NULL;
	return timetype;
}

/**
 * i_cal_timetype_get_year:
 * @timetype: The #ICalTimetype to be queried.
 *
 * Returns: The year.
 *
 * Get the year of #ICalTimetype.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_timetype_get_year (ICalTimetype *timetype)
{
	g_return_val_if_fail (timetype == NULL, 0);
	return i_cal_timetype_get_native_pointer_set_owner (timetype)->year;
}

/**
 * i_cal_timetype_get_month:
 * @timetype: The #ICalTimetype to be queried.
 *
 * Returns: The month.
 *
 * Get the month of #ICalTimetype.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_timetype_get_month (ICalTimetype *timetype)
{
	g_return_val_if_fail (timetype == NULL, 0);
	return i_cal_timetype_get_native_pointer_set_owner (timetype)->month;
}

/**
 * i_cal_timetype_get_day:
 * @timetype: The #ICalTimetype to be queried.
 *
 * Returns: The day.
 *
 * Get the day of #ICalTimetype.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_timetype_get_day (ICalTimetype *timetype)
{
	g_return_val_if_fail (timetype == NULL, 0);
	return i_cal_timetype_get_native_pointer_set_owner (timetype)->day;
}

/**
 * i_cal_timetype_get_hour:
 * @timetype: The #ICalTimetype to be queried.
 *
 * Returns: The hour.
 *
 * Get the hour of #ICalTimetype.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_timetype_get_hour (ICalTimetype *timetype)
{
	g_return_val_if_fail (timetype == NULL, 0);
	return i_cal_timetype_get_native_pointer_set_owner (timetype)->hour;
}

/**
 * i_cal_timetype_get_minute:
 * @timetype: The #ICalTimetype to be queried.
 *
 * Returns: The minute.
 *
 * Get the minute of #ICalTimetype.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_timetype_get_minute (ICalTimetype *timetype)
{
	g_return_val_if_fail (timetype == NULL, 0);
	return i_cal_timetype_get_native_pointer_set_owner (timetype)->minute;
}

/**
 * i_cal_timetype_get_second:
 * @timetype: The #ICalTimetype to be queried.
 *
 * Returns: The second.
 *
 * Get the second of #ICalTimetype.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_timetype_get_second (ICalTimetype *timetype)
{
	g_return_val_if_fail (timetype == NULL, 0);
	return i_cal_timetype_get_native_pointer_set_owner (timetype)->second;
}

/**
 * i_cal_timetype_is_utc:
 * @timetype: The #ICalTimetype to be queried.
 *
 * Returns: The is_utc.
 *
 * Get the is_utc of #ICalTimetype.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_timetype_is_utc (ICalTimetype *timetype)
{
	g_return_val_if_fail (timetype == NULL, 0);
	return i_cal_timetype_get_native_pointer_set_owner (timetype)->is_utc;
}

/**
 * i_cal_timetype_is_date:
 * @timetype: The #ICalTimetype to be queried.
 *
 * Returns: The is_date.
 *
 * Get the is_date of #ICalTimetype.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_timetype_is_date (ICalTimetype *timetype)
{
	g_return_val_if_fail (timetype == NULL, 0);
	return i_cal_timetype_get_native_pointer_set_owner (timetype)->is_date;
}

/**
 * i_cal_timetype_is_daylight:
 * @timetype: The #ICalTimetype to be queried.
 *
 * Returns: The is_daylight.
 *
 * Get the is_daylight of #ICalTimetype.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_timetype_is_daylight (ICalTimetype *timetype)
{
	g_return_val_if_fail (timetype == NULL, 0);
	return i_cal_timetype_get_native_pointer_set_owner (timetype)->is_daylight;
}

/**
 * i_cal_timetype_get_zone:
 * @timetype: The #ICalTimetype to be queried.
 *
 * Returns: The timezone.
 *
 * Get the is_daylight of #ICalTimetype.
 *
 * Since: 1.0
 *
 **/
const ICalTimezone *
i_cal_timetype_get_zone (ICalTimetype *timetype)
{
	g_return_val_if_fail (timetype == NULL, 0);
	return i_cal_timezone_new_full ((void *)i_cal_timetype_get_native_pointer_set_owner (timetype)->zone, NULL, TRUE);
}


