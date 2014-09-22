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
#ifndef I_CAL_DURATION_TYPE_H
#define I_CAL_DURATION_TYPE_H

#include "common-header.h"
#include "i-cal-enums.h"


G_BEGIN_DECLS

/* Standard GObject macros */
#define I_CAL_DURATION_TYPE_TYPE \
        (i_cal_duration_type_get_type ())
#define I_CAL_DURATION_TYPE(obj) \
        (G_TYPE_CHECK_INSTANCE_CAST \
        ((obj), I_CAL_DURATION_TYPE_TYPE, ICalDurationType))
#define I_CAL_DURATION_TYPE_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST \
        ((klass), I_CAL_DURATION_TYPE_TYPE, ICalDurationTypeClass))
#define I_CAL_IS_DURATION_TYPE(obj) \
        (G_TYPE_CHECK_INSTANCE_TYPE \
        ((obj), I_CAL_DURATION_TYPE_TYPE))
#define I_CAL_IS_DURATION_TYPE_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_TYPE \
        ((klass), I_CAL_DURATION_TYPE_TYPE))

typedef struct _ICalDurationType ICalDurationType;
typedef struct _ICalDurationTypeClass ICalDurationTypeClass;

struct _ICalDurationType {
	ICalObject parent;
};

struct _ICalDurationTypeClass {
	ICalObjectClass parent;
};


ICalDurationType *
		i_cal_duration_type_new_full	(struct icaldurationtype native);
GType 		i_cal_duration_type_get_type	(void);
struct icaldurationtype 
		i_cal_duration_type_get_native_set_owner
						(const ICalDurationType *object);
struct icaldurationtype 
		i_cal_duration_type_get_native_remove_owner
						(ICalDurationType *object);
struct icaldurationtype 
		i_cal_duration_type_steal_native
						(ICalDurationType *object);
struct icaldurationtype *
		i_cal_duration_type_get_native_pointer_set_owner
						(ICalDurationType *object);
ICalDurationType *
		i_cal_duration_type_from_int	(gint t);
ICalDurationType *
		i_cal_duration_type_from_string	(const gchar *str);
gint 		i_cal_duration_type_as_int	(ICalDurationType *duration);
gchar *		i_cal_duration_type_as_ical_string_r
						(ICalDurationType *duration);
ICalDurationType *
		i_cal_duration_type_null_duration
						(void);
ICalDurationType *
		i_cal_duration_type_bad_duration
						(void);
gint 		i_cal_duration_type_is_null_duration
						(ICalDurationType *duration);
gint 		i_cal_duration_type_is_bad_duration
						(ICalDurationType *duration);

G_END_DECLS

#endif /* I_CAL_DURATION_TYPE_H */
