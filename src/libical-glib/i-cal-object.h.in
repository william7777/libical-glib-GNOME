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
#ifndef I_CAL_OBJECT_H
#define I_CAL_OBJECT_H

#include <glib-object.h>
#include <stdio.h>
#include <libical/ical.h>

/* Standard GObject macros */
#define I_CAL_TYPE_OBJECT \
	(i_cal_object_get_type ())
#define I_CAL_OBJECT(obj) \
	(G_TYPE_CHECK_INSTANCE_CAST \
	((obj), I_CAL_TYPE_OBJECT, ICalObject))
#define I_CAL_OBJECT_CLASS(cls) \
	(G_TYPE_CHECK_CLASS_CAST \
	((cls), I_CAL_TYPE_OBJECT, ICalObjectClass))
#define I_CAL_IS_OBJECT(obj) \
	(G_TYPE_CHECK_INSTANCE_TYPE \
	((obj), I_CAL_TYPE_OBJECT))
#define I_CAL_IS_OBJECT_CLASS(cls) \
	(G_TYPE_CHECK_CLASS_TYPE \
	((cls), I_CAL_TYPE_OBJECT))
#define I_CAL_OBJECT_GET_CLASS(obj) \
	(G_TYPE_INSTANCE_GET_CLASS \
	((obj), I_CAL_TYPE_OBJECT, ICalObjectClass))

G_BEGIN_DECLS

typedef struct _ICalObject ICalObject;
typedef struct _ICalObjectClass ICalObjectClass;
typedef struct _ICalObjectPrivate ICalObjectPrivate;

struct _ICalObject {
	GObject parent;
	ICalObjectPrivate *priv;
};

struct _ICalObjectClass {
	GObjectClass parent_class;
};

GType		i_cal_object_get_type		(void);
void		i_cal_object_construct		(ICalObject *iobject,
						 gpointer native,
						 GDestroyNotify native_destroy_func,
						 gboolean is_global_memory,
						 GObject *owner);
gpointer	i_cal_object_get_native		(ICalObject *iobject);
gpointer	i_cal_object_steal_native	(ICalObject *iobject);
gboolean	i_cal_object_get_is_global_memory
						(ICalObject *iobject);
GDestroyNotify	i_cal_object_get_native_destroy_func
						(ICalObject *iobject);
void		i_cal_object_set_native_destroy_func
						(ICalObject *iobject,
						 GDestroyNotify native_destroy_func);
void		i_cal_object_set_owner		(ICalObject *iobject,
						 GObject *owner);
GObject *	i_cal_object_ref_owner		(ICalObject *iobject);
void	i_cal_object_remove_owner		(ICalObject *iobject);
void		i_cal_object_add_depender	(ICalObject *iobject,
						 GObject *depender);
void		i_cal_object_remove_depender	(ICalObject *iobject,
						 GObject *depender);

G_END_DECLS

#endif /* I_CAL_OBJECT_H */
