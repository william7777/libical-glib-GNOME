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
#ifndef I_CAL_TIMEZONE_H
#define I_CAL_TIMEZONE_H

#include "common-header.h"
#include "i-cal-enums.h"


G_BEGIN_DECLS

/* Standard GObject macros */
#define I_CAL_TIMEZONE_TYPE \
        (i_cal_timezone_get_type ())
#define I_CAL_TIMEZONE(obj) \
        (G_TYPE_CHECK_INSTANCE_CAST \
        ((obj), I_CAL_TIMEZONE_TYPE, ICalTimezone))
#define I_CAL_TIMEZONE_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST \
        ((klass), I_CAL_TIMEZONE_TYPE, ICalTimezoneClass))
#define I_CAL_IS_TIMEZONE(obj) \
        (G_TYPE_CHECK_INSTANCE_TYPE \
        ((obj), I_CAL_TIMEZONE_TYPE))
#define I_CAL_IS_TIMEZONE_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_TYPE \
        ((klass), I_CAL_TIMEZONE_TYPE))

typedef struct _ICalTimezone ICalTimezone;
typedef struct _ICalTimezoneClass ICalTimezoneClass;

struct _ICalTimezone {
	ICalObject parent;
};

struct _ICalTimezoneClass {
	ICalObjectClass parent;
};
typedef struct _ICalComponent ICalComponent;


ICalTimezone *	i_cal_timezone_new_full		(icaltimezone *native,
						 GObject *owner,
						 gboolean is_global_memory);
GType 		i_cal_timezone_get_type		(void);
icaltimezone *	i_cal_timezone_get_native_set_owner
						(const ICalTimezone *object,
						 GObject *owner);
icaltimezone *	i_cal_timezone_get_native_remove_owner
						(ICalTimezone *object);
icaltimezone *	i_cal_timezone_steal_native	(ICalTimezone *object);
ICalTimezone *	i_cal_timezone_new		(void);
void		i_cal_timezone_destroy		(icaltimezone *zone);
ICalTimezone *	i_cal_timezone_copy		(const ICalTimezone *zone);
void		i_cal_timezone_free		(ICalTimezone *zone,
						 gint free_struct);
void		i_cal_timezone_set_tzid_prefix	(const gchar *new_prefix);
void		i_cal_timezone_free_builtin_timezones
						(void);
ICalTimezone *	i_cal_timezone_get_builtin_timezone
						(const gchar *location);
ICalTimezone *	i_cal_timezone_get_builtin_timezone_from_offset
						(gint offset,
						 const gchar *tzname);
ICalTimezone *	i_cal_timezone_get_builtin_timezone_from_tzid
						(const gchar *tzid);
ICalTimezone *	i_cal_timezone_get_utc_timezone	(void);
const gchar *	i_cal_timezone_get_tzid		(const ICalTimezone *zone);
const gchar *	i_cal_timezone_get_location	(const ICalTimezone *zone);
const gchar *	i_cal_timezone_get_tznames	(const ICalTimezone *zone);
gdouble 		i_cal_timezone_get_latitude	(const ICalTimezone *zone);
gdouble 		i_cal_timezone_get_longitude	(const ICalTimezone *zone);
ICalComponent *	i_cal_timezone_get_component	(const ICalTimezone *zone);
gint 		i_cal_timezone_set_component	(ICalTimezone *zone,
						 ICalComponent *comp);
const gchar *	i_cal_timezone_get_display_name	(const ICalTimezone *zone);
void		i_cal_timezone_release_zone_tab	(void);

G_END_DECLS

#endif /* I_CAL_TIMEZONE_H */
