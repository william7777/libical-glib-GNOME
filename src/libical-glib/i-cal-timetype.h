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
#ifndef I_CAL_TIMETYPE_H
#define I_CAL_TIMETYPE_H

#include "common-header.h"
#include "i-cal-enums.h"


G_BEGIN_DECLS

/* Standard GObject macros */
#define I_CAL_TIMETYPE_TYPE \
        (i_cal_timetype_get_type ())
#define I_CAL_TIMETYPE(obj) \
        (G_TYPE_CHECK_INSTANCE_CAST \
        ((obj), I_CAL_TIMETYPE_TYPE, ICalTimetype))
#define I_CAL_TIMETYPE_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST \
        ((klass), I_CAL_TIMETYPE_TYPE, ICalTimetypeClass))
#define I_CAL_IS_TIMETYPE(obj) \
        (G_TYPE_CHECK_INSTANCE_TYPE \
        ((obj), I_CAL_TIMETYPE_TYPE))
#define I_CAL_IS_TIMETYPE_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_TYPE \
        ((klass), I_CAL_TIMETYPE_TYPE))

typedef struct _ICalTimetype ICalTimetype;
typedef struct _ICalTimetypeClass ICalTimetypeClass;

struct _ICalTimetype {
	ICalObject parent;
};

struct _ICalTimetypeClass {
	ICalObjectClass parent;
};
typedef struct _ICalTimezone ICalTimezone;


ICalTimetype *	i_cal_timetype_new_full		(icaltimetype native);
GType 		i_cal_timetype_get_type		(void);
icaltimetype 	i_cal_timetype_get_native_set_owner
						(const ICalTimetype *object);
icaltimetype 	i_cal_timetype_get_native_remove_owner
						(ICalTimetype *object);
icaltimetype 	i_cal_timetype_steal_native	(ICalTimetype *object);
icaltimetype *	i_cal_timetype_get_native_pointer_set_owner
						(ICalTimetype *object);
icaltimetype 	i_cal_timetype_new		(void);
gint 		i_cal_timetype_get_year		(ICalTimetype *timetype);
gint 		i_cal_timetype_get_month	(ICalTimetype *timetype);
gint 		i_cal_timetype_get_day		(ICalTimetype *timetype);
gint 		i_cal_timetype_get_hour		(ICalTimetype *timetype);
gint 		i_cal_timetype_get_minute	(ICalTimetype *timetype);
gint 		i_cal_timetype_get_second	(ICalTimetype *timetype);
gint 		i_cal_timetype_is_utc		(ICalTimetype *timetype);
gint 		i_cal_timetype_is_date		(ICalTimetype *timetype);
gint 		i_cal_timetype_is_daylight	(ICalTimetype *timetype);
const ICalTimezone *
		i_cal_timetype_get_zone		(ICalTimetype *timetype);

G_END_DECLS

#endif /* I_CAL_TIMETYPE_H */
