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

#include "i-cal-time.h"
#include "i-cal-timetype.h"
#include "i-cal-timezone.h"



/**
 * i_cal_time_null_time:
 *
 * Returns: (transfer full): The newly created #ICalTimetype
 *
 * Create a default time which is an epoch time
 *
 * Since: 1.0
 *
 **/
ICalTimetype *
i_cal_time_null_time (void)
{
	return i_cal_timetype_new_full (icaltime_null_time ()) ;
}

/**
 * i_cal_time_null_date:
 *
 * Returns: (transfer full): The newly created #ICalTimetype
 *
 * Create a null date, which indicates no time has been set
 *
 * Since: 1.0
 *
 **/
ICalTimetype *
i_cal_time_null_date (void)
{
	return i_cal_timetype_new_full (icaltime_null_date ()) ;
}

/**
 * i_cal_time_current_time_with_zone:
 * @zone: (in) (transfer none): The timezone used to create a #ICalTimetype according to the current time
 *
 * Returns: (transfer full): The newly created #ICalTimetype
 *
 * Create a #ICalTimetype according to the timezone and current time
 *
 * Since: 1.0
 *
 **/
ICalTimetype *
i_cal_time_current_time_with_zone (ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), NULL);
	g_return_val_if_fail (zone != NULL, NULL);

	return i_cal_timetype_new_full (icaltime_current_time_with_zone (i_cal_timezone_get_native_set_owner (zone, NULL))) ;
}

/**
 * i_cal_time_today:
 *
 * Returns: (transfer full): The newly created #ICalTimetype
 *
 * Create a #ICalTimetype representing today
 *
 * Since: 1.0
 *
 **/
ICalTimetype *
i_cal_time_today (void)
{
	return i_cal_timetype_new_full (icaltime_today ()) ;
}

/**
 * i_cal_time_from_timet:
 * @v: The seconds past since epoch time
 * @is_date: Whether it is a date type, 1 if yes, 0 if not.
 *
 * Returns: (transfer full): The newly created #ICalTimetype
 *
 * Convert seconds past UNIX epoch to a timetype
 *
 * Since: 1.0
 *
 **/
ICalTimetype *
i_cal_time_from_timet (const time_t v, 
                       gint is_date)
{
	return i_cal_timetype_new_full (icaltime_from_timet (v, is_date)) ;
}

/**
 * i_cal_time_from_timet_with_zone:
 * @v: The seconds past since epoch time
 * @is_date: Whether it is a date type, 1 if yes, 0 if not.
 * @zone: (in) (transfer none): The timezone
 *
 * Returns: (transfer full): The newly created #ICalTimetype
 *
 * Convert seconds past UNIX epoch to a timetype, using timezones.
 *
 * Since: 1.0
 *
 **/
ICalTimetype *
i_cal_time_from_timet_with_zone (const time_t v, 
                                 gint is_date, 
                                 ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), NULL);
	g_return_val_if_fail (zone != NULL, NULL);

	return i_cal_timetype_new_full (icaltime_from_timet_with_zone (v, is_date, i_cal_timezone_get_native_set_owner (zone, NULL))) ;
}

/**
 * i_cal_time_from_string:
 * @str: The ISO format string
 *
 * Returns: (transfer full): The newly created #ICalTimetype
 *
 * create a time from an ISO format string
 *
 * Since: 1.0
 *
 **/
ICalTimetype *
i_cal_time_from_string (const gchar *str)
{
	g_return_val_if_fail (str != NULL, NULL);

	return i_cal_timetype_new_full (icaltime_from_string (str)) ;
}

/**
 * i_cal_time_from_day_of_year:
 * @day: The day of a year
 * @year: The year
 *
 * Returns: (transfer full): The newly created #ICalTimetype
 *
 * Create a new time, given a day of year and a year.
 *
 * Since: 1.0
 *
 **/
ICalTimetype *
i_cal_time_from_day_of_year (const gint day, 
                             const gint year)
{
	return i_cal_timetype_new_full (icaltime_from_day_of_year (day, year)) ;
}

/**
 * i_cal_time_as_timet:
 * @tt: The #ICalTimetype to be converted
 *
 * Returns: the time as seconds past the UNIX epoch
 *
 * Return the time as seconds past the UNIX epoch
 *
 * Since: 1.0
 *
 **/
time_t
i_cal_time_as_timet (ICalTimetype *tt)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), 0);
	g_return_val_if_fail (tt != NULL, 0);

	return icaltime_as_timet (i_cal_timetype_get_native_set_owner (tt));
}

/**
 * i_cal_time_as_timet_with_zone:
 * @tt: The #ICalTimetype to be converted
 * @zone: (in) (transfer none): The timezone
 *
 * Returns: the time as seconds past the UNIX epoch
 *
 * Return the time as seconds past the UNIX epoch, using timezones.
 *
 * Since: 1.0
 *
 **/
time_t
i_cal_time_as_timet_with_zone (ICalTimetype *tt, 
                               ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), 0);
	g_return_val_if_fail (tt != NULL, 0);
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), 0);
	g_return_val_if_fail (zone != NULL, 0);

	return icaltime_as_timet_with_zone (i_cal_timetype_get_native_set_owner (tt), i_cal_timezone_get_native_set_owner (zone, NULL));
}

/**
 * i_cal_time_as_ical_string_r:
 * @tt: The #ICalTimetype to be converted
 *
 * Returns: (transfer full): The string representation
 *
 * Return a string represention of the time, in RFC2445 format.
 *
 * Since: 1.0
 *
 **/
gchar *
i_cal_time_as_ical_string_r (ICalTimetype *tt)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), NULL);
	g_return_val_if_fail (tt != NULL, NULL);

	return icaltime_as_ical_string_r (i_cal_timetype_get_native_set_owner (tt));
}

/**
 * i_cal_time_get_timezone:
 * @tt: (in) (transfer none): The #ICalTimetype to be queried
 *
 * Returns: (transfer full): The timezone information
 *
 * Return the timezone
 *
 * Since: 1.0
 *
 **/
const ICalTimezone *
i_cal_time_get_timezone (ICalTimetype *tt)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), NULL);
	g_return_val_if_fail (tt != NULL, NULL);

	return i_cal_timezone_new_full ((void *)icaltime_get_timezone (i_cal_timetype_get_native_set_owner (tt)), (GObject *)tt, TRUE) ;
}

/**
 * i_cal_time_set_timezone:
 * @tt: The #ICalTimetype to be queried
 * @zone: (transfer full): The timezone
 *
 * Returns: (transfer full): The #ICalTimetype after being set
 *
 * Set the timezone
 *
 * Since: 1.0
 *
 **/
ICalTimetype *
i_cal_time_set_timezone (ICalTimetype *tt, 
                         ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), NULL);
	g_return_val_if_fail (tt != NULL, NULL);
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), NULL);
	g_return_val_if_fail (zone != NULL, NULL);

	return i_cal_timetype_new_full (icaltime_set_timezone (i_cal_timetype_get_native_pointer_set_owner (tt), i_cal_timezone_get_native_set_owner (zone, NULL))) ;
}

/**
 * i_cal_time_get_tzid:
 * @tt: (in) (transfer none): The #ICalTimetype to be queried
 *
 * Returns: (allow-none) (transfer none): The tzid of #ICalTimetype, or NULL if floating type
 *
 * Return the tzid, or NULL for a floating time
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_time_get_tzid (ICalTimetype *tt)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), NULL);
	g_return_val_if_fail (tt != NULL, NULL);

	return icaltime_get_tzid (i_cal_timetype_get_native_set_owner (tt));
}

/**
 * i_cal_time_day_of_year:
 * @tt: (in) (transfer none): The #ICalTimetype to be queried
 *
 * Returns: the day of the year of the given time
 *
 * Return the day of the year of the given time
 *
 * Since: 1.0
 *
 **/
gint
i_cal_time_day_of_year (ICalTimetype *tt)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), 0);
	g_return_val_if_fail (tt != NULL, 0);

	return icaltime_day_of_year (i_cal_timetype_get_native_set_owner (tt));
}

/**
 * i_cal_time_day_of_week:
 * @tt: (in) (transfer none): The #ICalTimetype to be queried
 *
 * Returns: the day of the week of the given time. Sunday is 1.
 *
 * Return the day of the week of the given time. Sunday is 1
 *
 * Since: 1.0
 *
 **/
gint
i_cal_time_day_of_week (ICalTimetype *tt)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), 0);
	g_return_val_if_fail (tt != NULL, 0);

	return icaltime_day_of_week (i_cal_timetype_get_native_set_owner (tt));
}

/**
 * i_cal_time_start_doy_of_week:
 * @tt: (in) (transfer none): The #ICalTimetype to be queried
 *
 * Returns: the day of the year for the Sunday of the week that the given time is within.
 *
 * Return the day of the year for the Sunday of the week that the given time is within.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_time_start_doy_of_week (ICalTimetype *tt)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), 0);
	g_return_val_if_fail (tt != NULL, 0);

	return icaltime_start_doy_of_week (i_cal_timetype_get_native_set_owner (tt));
}

/**
 * i_cal_time_start_doy_week:
 * @tt: (in) (transfer none): The #ICalTimetype to be queried
 * @fdow: The first day of the week
 *
 * Returns: the day of the year for the Sunday of the week that the given time is within.
 *
 * Return the day of the year for the first day of the week that the given time is within.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_time_start_doy_week (ICalTimetype *tt, 
                           gint fdow)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), 0);
	g_return_val_if_fail (tt != NULL, 0);

	return icaltime_start_doy_week (i_cal_timetype_get_native_set_owner (tt), fdow);
}

/**
 * i_cal_time_week_number:
 * @tt: (in) (transfer none): The #ICalTimetype to be queried
 *
 * Returns: the week number for the week the given time is within.
 *
 * Return the week number for the week the given time is within.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_time_week_number (ICalTimetype *tt)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), 0);
	g_return_val_if_fail (tt != NULL, 0);

	return icaltime_week_number (i_cal_timetype_get_native_set_owner (tt));
}

/**
 * i_cal_time_is_null_time:
 * @tt: (in) (transfer none): The #ICalTimetype to be checked
 *
 * Returns: Whether @tt is null_time. 1 if yes, 0 if not.
 *
 * Return true of the time is null.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_time_is_null_time (ICalTimetype *tt)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), 0);
	g_return_val_if_fail (tt != NULL, 0);

	return icaltime_is_null_time (i_cal_timetype_get_native_set_owner (tt));
}

/**
 * i_cal_time_is_valid_time:
 * @tt: (in) (transfer none): The #ICalTimetype to be checked
 *
 * Returns: Whether @tt is null_time. 1 if yes, 0 if not.
 *
 * Return true of the time is null.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_time_is_valid_time (ICalTimetype *tt)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), 0);
	g_return_val_if_fail (tt != NULL, 0);

	return icaltime_is_valid_time (i_cal_timetype_get_native_set_owner (tt));
}

/**
 * i_cal_time_is_date:
 * @tt: (in) (transfer none): The #ICalTimetype to be checked
 *
 * Returns: true if time is of DATE type, false if DATE-TIME.
 *
 * Returns true if time is of DATE type, false if DATE-TIME.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_time_is_date (ICalTimetype *tt)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), 0);
	g_return_val_if_fail (tt != NULL, 0);

	return icaltime_is_date (i_cal_timetype_get_native_set_owner (tt));
}

/**
 * i_cal_time_is_utc:
 * @tt: (in) (transfer none): The #ICalTimetype to be checked
 *
 * Returns: true if time is relative to UTC zone.
 *
 * Returns true if time is relative to UTC zone.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_time_is_utc (ICalTimetype *tt)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (tt), 0);
	g_return_val_if_fail (tt != NULL, 0);

	return icaltime_is_utc (i_cal_timetype_get_native_set_owner (tt));
}

/**
 * i_cal_time_compare:
 * @a: (in) (transfer none): The #ICalTimetype to be compared
 * @b: (in) (transfer none): The #ICalTimetype to be compared
 *
 * Returns: -1, 0, or 1 to indicate that a less than b, a==b or a larger than b.
 *
 * Return -1, 0, or 1 to indicate that a less than b, a==b or a larger than b.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_time_compare (ICalTimetype *a, 
                    ICalTimetype *b)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (a), 0);
	g_return_val_if_fail (a != NULL, 0);
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (b), 0);
	g_return_val_if_fail (b != NULL, 0);

	return icaltime_compare (i_cal_timetype_get_native_set_owner (a), i_cal_timetype_get_native_set_owner (b));
}

/**
 * i_cal_time_compare_date_only:
 * @a: (in) (transfer none): The #ICalTimetype to be compared
 * @b: (in) (transfer none): The #ICalTimetype to be compared
 *
 * Returns: -1, 0, or 1 to indicate that a less than b, a==b or a larger than b.
 *
 * like icaltime_compare, but only use the date parts.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_time_compare_date_only (ICalTimetype *a, 
                              ICalTimetype *b)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (a), 0);
	g_return_val_if_fail (a != NULL, 0);
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (b), 0);
	g_return_val_if_fail (b != NULL, 0);

	return icaltime_compare_date_only (i_cal_timetype_get_native_set_owner (a), i_cal_timetype_get_native_set_owner (b));
}

/**
 * i_cal_time_compare_date_only_tz:
 * @a: (in) (transfer none): The #ICalTimetype to be compared
 * @b: (in) (transfer none): The #ICalTimetype to be compared
 * @zone: (transfer full): The target timezone
 *
 * Returns: -1, 0, or 1 to indicate that a less than b, a==b or a larger than b.
 *
 * like icaltime_compare_tz, but only use the date parts.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_time_compare_date_only_tz (ICalTimetype *a, 
                                 ICalTimetype *b, 
                                 ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (a), 0);
	g_return_val_if_fail (a != NULL, 0);
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (b), 0);
	g_return_val_if_fail (b != NULL, 0);
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), 0);
	g_return_val_if_fail (zone != NULL, 0);

	return icaltime_compare_date_only_tz (i_cal_timetype_get_native_set_owner (a), i_cal_timetype_get_native_set_owner (b), i_cal_timezone_get_native_set_owner (zone, NULL));
}

/**
 * i_cal_time_adjust:
 * @tt: The #ICalTimetype to be set
 * @days: difference of days adjusted
 * @hours: difference of hours adjusted
 * @minutes: difference of minutes adjusted
 * @seconds: difference of seconds adjusted
 *
 * like icaltime_compare_tz, but only use the date parts.
 *
 * Since: 1.0
 *
 **/
void
i_cal_time_adjust (ICalTimetype *tt, 
                   const gint days, 
                   const gint hours, 
                   const gint minutes, 
                   const gint seconds)
{
	g_return_if_fail (I_CAL_IS_TIMETYPE (tt));
	g_return_if_fail (tt != NULL);

	icaltime_adjust (i_cal_timetype_get_native_pointer_set_owner (tt), days, hours, minutes, seconds);
}

/**
 * i_cal_time_normalize:
 * @t: (in) (transfer none): The #ICalTimetype to be normalized
 *
 * Returns: (transfer full): The #ICalTimetype normalized
 *
 * Normalize the icaltime, so that all fields are within the normal range.
 *
 * Since: 1.0
 *
 **/
ICalTimetype *
i_cal_time_normalize (ICalTimetype *t)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (t), NULL);
	g_return_val_if_fail (t != NULL, NULL);

	return i_cal_timetype_new_full (icaltime_normalize (i_cal_timetype_get_native_set_owner (t))) ;
}

/**
 * i_cal_time_convert_to_zone:
 * @t: (in) (transfer none): The #ICalTimetype to be normalized
 * @zone: (transfer full): The target timezone
 *
 * Returns: (transfer full): The converted #ICalTimetype
 *
 * Convert tt, of timezone tzid, into a utc time. Does nothing if the time is already UTC.
 *
 * Since: 1.0
 *
 **/
ICalTimetype *
i_cal_time_convert_to_zone (ICalTimetype *t, 
                            ICalTimezone *zone)
{
	g_return_val_if_fail (I_CAL_IS_TIMETYPE (t), NULL);
	g_return_val_if_fail (t != NULL, NULL);
	g_return_val_if_fail (I_CAL_IS_TIMEZONE (zone), NULL);
	g_return_val_if_fail (zone != NULL, NULL);

	return i_cal_timetype_new_full (icaltime_convert_to_zone (i_cal_timetype_get_native_set_owner (t), i_cal_timezone_get_native_set_owner (zone, NULL))) ;
}

/**
 * i_cal_time_days_in_month:
 * @month: The target month
 * @year: The target year
 *
 * Returns: The number of days in the target month in the target year.
 *
 * Get the number of days in the target month in the target year.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_time_days_in_month (const gint month, 
                          const gint year)
{
	return icaltime_days_in_month (month, year);
}


