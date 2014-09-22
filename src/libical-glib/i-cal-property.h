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
#ifndef I_CAL_PROPERTY_H
#define I_CAL_PROPERTY_H

#include "common-header.h"
#include "i-cal-enums.h"


G_BEGIN_DECLS

/* Standard GObject macros */
#define I_CAL_PROPERTY_TYPE \
        (i_cal_property_get_type ())
#define I_CAL_PROPERTY(obj) \
        (G_TYPE_CHECK_INSTANCE_CAST \
        ((obj), I_CAL_PROPERTY_TYPE, ICalProperty))
#define I_CAL_PROPERTY_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST \
        ((klass), I_CAL_PROPERTY_TYPE, ICalPropertyClass))
#define I_CAL_IS_PROPERTY(obj) \
        (G_TYPE_CHECK_INSTANCE_TYPE \
        ((obj), I_CAL_PROPERTY_TYPE))
#define I_CAL_IS_PROPERTY_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_TYPE \
        ((klass), I_CAL_PROPERTY_TYPE))

typedef struct _ICalProperty ICalProperty;
typedef struct _ICalPropertyClass ICalPropertyClass;

struct _ICalProperty {
	ICalObject parent;
};

struct _ICalPropertyClass {
	ICalObjectClass parent;
};


ICalProperty *	i_cal_property_new_full		(icalproperty *native,
						 GObject *owner);
GType 		i_cal_property_get_type		(void);
icalproperty *	i_cal_property_get_native_set_owner
						(const ICalProperty *object,
						 GObject *owner);
icalproperty *	i_cal_property_get_native_remove_owner
						(ICalProperty *object);
icalproperty *	i_cal_property_steal_native	(ICalProperty *object);

G_END_DECLS

#endif /* I_CAL_PROPERTY_H */
