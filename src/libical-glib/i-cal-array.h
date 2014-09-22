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
#ifndef I_CAL_ARRAY_H
#define I_CAL_ARRAY_H

#include "common-header.h"
#include "i-cal-enums.h"


G_BEGIN_DECLS

/* Standard GObject macros */
#define I_CAL_ARRAY_TYPE \
        (i_cal_array_get_type ())
#define I_CAL_ARRAY(obj) \
        (G_TYPE_CHECK_INSTANCE_CAST \
        ((obj), I_CAL_ARRAY_TYPE, ICalArray))
#define I_CAL_ARRAY_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST \
        ((klass), I_CAL_ARRAY_TYPE, ICalArrayClass))
#define I_CAL_IS_ARRAY(obj) \
        (G_TYPE_CHECK_INSTANCE_TYPE \
        ((obj), I_CAL_ARRAY_TYPE))
#define I_CAL_IS_ARRAY_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_TYPE \
        ((klass), I_CAL_ARRAY_TYPE))

typedef struct _ICalArray ICalArray;
typedef struct _ICalArrayClass ICalArrayClass;

struct _ICalArray {
	ICalObject parent;
};

struct _ICalArrayClass {
	ICalObjectClass parent;
};


ICalArray *	i_cal_array_new_full		(icalarray *native,
						 GObject *owner);
GType 		i_cal_array_get_type		(void);
icalarray *	i_cal_array_get_native_set_owner
						(const ICalArray *object,
						 GObject *owner);
icalarray *	i_cal_array_get_native_remove_owner
						(ICalArray *object);
icalarray *	i_cal_array_steal_native	(ICalArray *object);
ICalArray *	i_cal_array_new			(gint element_size,
						 gint increment_size);
ICalArray *	i_cal_array_copy		(ICalArray *array);
void		i_cal_array_free		(ICalArray *array);
void		i_cal_array_append		(ICalArray *array,
						 gconstpointer element);
void		i_cal_array_remove_element_at	(ICalArray *array,
						 gint position);
const void *	i_cal_array_element_at		(ICalArray *array,
						 gint position);
void		i_cal_array_sort		(ICalArray *array,
						 GCompareFunc compare);

G_END_DECLS

#endif /* I_CAL_ARRAY_H */
