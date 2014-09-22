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
#ifndef I_CAL_ATTACH_H
#define I_CAL_ATTACH_H

#include "common-header.h"
#include "i-cal-enums.h"


G_BEGIN_DECLS

/* Standard GObject macros */
#define I_CAL_ATTACH_TYPE \
        (i_cal_attach_get_type ())
#define I_CAL_ATTACH(obj) \
        (G_TYPE_CHECK_INSTANCE_CAST \
        ((obj), I_CAL_ATTACH_TYPE, ICalAttach))
#define I_CAL_ATTACH_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST \
        ((klass), I_CAL_ATTACH_TYPE, ICalAttachClass))
#define I_CAL_IS_ATTACH(obj) \
        (G_TYPE_CHECK_INSTANCE_TYPE \
        ((obj), I_CAL_ATTACH_TYPE))
#define I_CAL_IS_ATTACH_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_TYPE \
        ((klass), I_CAL_ATTACH_TYPE))

typedef struct _ICalAttach ICalAttach;
typedef struct _ICalAttachClass ICalAttachClass;

struct _ICalAttach {
	ICalObject parent;
};

struct _ICalAttachClass {
	ICalObjectClass parent;
};


ICalAttach *	i_cal_attach_new_full		(icalattach *native,
						 GObject *owner);
GType 		i_cal_attach_get_type		(void);
icalattach *	i_cal_attach_get_native_set_owner
						(const ICalAttach *object,
						 GObject *owner);
icalattach *	i_cal_attach_get_native_remove_owner
						(ICalAttach *object);
icalattach *	i_cal_attach_steal_native	(ICalAttach *object);
ICalAttach *	i_cal_attach_new_from_url	(const gchar *url);
ICalAttach *	i_cal_attach_new_from_data	(const gchar *data,
						 GFunc free_fn,
						 void *free_fn_data);
void		i_cal_attach_ref		(ICalAttach *attach);
void		i_cal_attach_unref		(ICalAttach *attach);
gint 		i_cal_attach_get_is_url		(ICalAttach *attach);
const gchar *	i_cal_attach_get_url		(ICalAttach *attach);
guchar *	i_cal_attach_get_data		(ICalAttach *attach);

G_END_DECLS

#endif /* I_CAL_ATTACH_H */
