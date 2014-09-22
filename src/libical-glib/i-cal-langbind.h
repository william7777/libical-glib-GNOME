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
#ifndef I_CAL_LANGBIND_H
#define I_CAL_LANGBIND_H

#include "common-header.h"
#include "i-cal-enums.h"


G_BEGIN_DECLS


typedef struct _ICalComponent ICalComponent;
typedef struct _ICalProperty ICalProperty;


gint *		i_cal_langbind_new_array	(gint size);
void		i_cal_langbind_free_array	(gint *array);
gint 		i_cal_langbind_access_array	(gint *array,
						 gint index);
ICalParameter *	i_cal_langbind_get_first_parameter
						(ICalProperty *prop);
ICalParameter *	i_cal_langbind_get_next_parameter
						(ICalProperty *prop);
ICalProperty *	i_cal_langbind_get_first_property
						(ICalComponent *c,
						 const gchar *prop);
ICalProperty *	i_cal_langbind_get_next_property
						(ICalComponent *c,
						 const gchar *prop);
ICalComponent *	i_cal_langbind_get_first_component
						(ICalComponent *c,
						 const gchar *comp);
ICalComponent *	i_cal_langbind_get_next_component
						(ICalComponent *c,
						 const gchar *comp);
gchar *		i_cal_langbind_property_eval_string_r
						(ICalProperty *prop,
						 gchar *sep);
gint 		i_cal_langbind_string_to_open_flag
						(const gchar *str);
gchar *		i_cal_langbind_quote_as_ical_r	(const gchar *str);

G_END_DECLS

#endif /* I_CAL_LANGBIND_H */
