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
/*
#if !defined (__LIBICAL_GLIB_H_INSIDE__) && !defined (LIBICAL_GLIB_COMPILATION)
#error "Only <libical-glib/libical-glib.h> can be included directly."
#endif
*/
#ifndef I_CAL_TIME_H
#define I_CAL_TIME_H

#include "common-header.h"
#include "i-cal-enums.h"


G_BEGIN_DECLS


typedef struct _ICalTimetype ICalTimetype;
typedef struct _ICalTimezone ICalTimezone;


ICalTimetype *	i_cal_time_null_time		(void);
ICalTimetype *	i_cal_time_null_date		(void);
ICalTimetype *	i_cal_time_current_time_with_zone
						(ICalTimezone *zone);
ICalTimetype *	i_cal_time_today		(void);
ICalTimetype *	i_cal_time_from_timet		(const time_t v,
						 gint is_date);
ICalTimetype *	i_cal_time_from_timet_with_zone	(const time_t v,
						 gint is_date,
						 ICalTimezone *zone);
ICalTimetype *	i_cal_time_from_string		(const gchar *str);
ICalTimetype *	i_cal_time_from_day_of_year	(const gint day,
						 const gint year);
time_t 		i_cal_time_as_timet		(ICalTimetype *tt);
time_t 		i_cal_time_as_timet_with_zone	(ICalTimetype *tt,
						 ICalTimezone *zone);
gchar *		i_cal_time_as_ical_string_r	(ICalTimetype *tt);
const ICalTimezone *
		i_cal_time_get_timezone		(ICalTimetype *tt);
ICalTimetype *	i_cal_time_set_timezone		(ICalTimetype *tt,
						 ICalTimezone *zone);
const gchar *	i_cal_time_get_tzid		(ICalTimetype *tt);
gint 		i_cal_time_day_of_year		(ICalTimetype *tt);
gint 		i_cal_time_day_of_week		(ICalTimetype *tt);
gint 		i_cal_time_start_doy_of_week	(ICalTimetype *tt);
gint 		i_cal_time_start_doy_week	(ICalTimetype *tt,
						 gint fdow);
gint 		i_cal_time_week_number		(ICalTimetype *tt);
gint 		i_cal_time_is_null_time		(ICalTimetype *tt);
gint 		i_cal_time_is_valid_time	(ICalTimetype *tt);
gint 		i_cal_time_is_date		(ICalTimetype *tt);
gint 		i_cal_time_is_utc		(ICalTimetype *tt);
gint 		i_cal_time_compare		(ICalTimetype *a,
						 ICalTimetype *b);
gint 		i_cal_time_compare_date_only	(ICalTimetype *a,
						 ICalTimetype *b);
gint 		i_cal_time_compare_date_only_tz	(ICalTimetype *a,
						 ICalTimetype *b,
						 ICalTimezone *zone);
void		i_cal_time_adjust		(ICalTimetype *tt,
						 const gint days,
						 const gint hours,
						 const gint minutes,
						 const gint seconds);
ICalTimetype *	i_cal_time_normalize		(ICalTimetype *t);
ICalTimetype *	i_cal_time_convert_to_zone	(ICalTimetype *t,
						 ICalTimezone *zone);
gint 		i_cal_time_days_in_month	(const gint month,
						 const gint year);

G_END_DECLS

#endif /* I_CAL_TIME_H */
