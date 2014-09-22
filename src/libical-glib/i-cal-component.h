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
#ifndef I_CAL_COMPONENT_H
#define I_CAL_COMPONENT_H

#include "common-header.h"
#include "i-cal-enums.h"


G_BEGIN_DECLS

/* Standard GObject macros */
#define I_CAL_COMPONENT_TYPE \
        (i_cal_component_get_type ())
#define I_CAL_COMPONENT(obj) \
        (G_TYPE_CHECK_INSTANCE_CAST \
        ((obj), I_CAL_COMPONENT_TYPE, ICalComponent))
#define I_CAL_COMPONENT_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_CAST \
        ((klass), I_CAL_COMPONENT_TYPE, ICalComponentClass))
#define I_CAL_IS_COMPONENT(obj) \
        (G_TYPE_CHECK_INSTANCE_TYPE \
        ((obj), I_CAL_COMPONENT_TYPE))
#define I_CAL_IS_COMPONENT_CLASS(klass) \
        (G_TYPE_CHECK_CLASS_TYPE \
        ((klass), I_CAL_COMPONENT_TYPE))

typedef struct _ICalComponent ICalComponent;
typedef struct _ICalComponentClass ICalComponentClass;

struct _ICalComponent {
	ICalObject parent;
};

struct _ICalComponentClass {
	ICalObjectClass parent;
};
typedef struct _ICalTimetype ICalTimetype;
typedef struct _ICalProperty ICalProperty;


ICalComponent *	i_cal_component_new_full	(icalcomponent *native,
						 GObject *owner);
GType 		i_cal_component_get_type	(void);
icalcomponent *	i_cal_component_get_native_set_owner
						(const ICalComponent *object,
						 GObject *owner);
icalcomponent *	i_cal_component_get_native_remove_owner
						(ICalComponent *object);
icalcomponent *	i_cal_component_steal_native	(ICalComponent *object);
ICalComponent *	i_cal_component_new		(ICalComponentKind kind);
ICalComponent *	i_cal_component_new_clone	(ICalComponent *component);
ICalComponent *	i_cal_component_new_from_string	(const gchar *str);
ICalComponent *	i_cal_component_new_x		(const gchar *x_name);
void		i_cal_component_free		(ICalComponent *component);
gchar *		i_cal_component_as_ical_string_r
						(ICalComponent *component);
gint 		i_cal_component_is_valid	(ICalComponent *component);
ICalComponentKind 
		i_cal_component_isa		(ICalComponent *component);
gint 		i_cal_component_isa_component	(ICalComponent *component);
void		i_cal_component_add_property	(ICalComponent *component,
						 ICalProperty *property);
void		i_cal_component_remove_property	(ICalComponent *component,
						 ICalProperty *property);
gint 		i_cal_component_count_properties
						(ICalComponent *component,
						 ICalPropertyKind kind);
ICalProperty *	i_cal_component_get_current_property
						(ICalComponent *component);
ICalProperty *	i_cal_component_get_first_property
						(ICalComponent *component,
						 ICalPropertyKind kind);
ICalProperty *	i_cal_component_get_next_property
						(ICalComponent *component,
						 ICalPropertyKind kind);
ICalComponent *	i_cal_component_get_inner	(ICalComponent *comp);
void		i_cal_component_add_component	(ICalComponent *parent,
						 ICalComponent *child);
void		i_cal_component_remove_component
						(ICalComponent *parent,
						 ICalComponent *child);
gint 		i_cal_component_count_components
						(ICalComponent *component,
						 ICalComponentKind kind);
void		i_cal_component_merge_component	(ICalComponent *comp,
						 ICalComponent *comp_to_merge);
ICalComponent *	i_cal_component_get_current_component
						(ICalComponent *component);
ICalComponent *	i_cal_component_get_first_component
						(ICalComponent *component,
						 ICalComponentKind kind);
ICalComponent *	i_cal_component_get_next_component
						(ICalComponent *component,
						 ICalComponentKind kind);
gint 		i_cal_component_check_restrictions
						(ICalComponent *comp);
gint 		i_cal_component_count_errors	(ICalComponent *comp);
void		i_cal_component_strip_errors	(ICalComponent *comp);
void		i_cal_component_convert_errors	(ICalComponent *comp);
gint 		i_cal_component_kind_is_valid	(const ICalComponentKind kind);
ICalComponentKind 
		i_cal_component_string_to_kind	(const gchar *string);
const gchar *	i_cal_component_kind_to_string	(ICalComponentKind kind);
ICalComponent *	i_cal_component_get_first_real_component
						(ICalComponent *c);
void		i_cal_component_set_summary	(ICalComponent *comp,
						 const gchar *v);
const gchar *	i_cal_component_get_summary	(ICalComponent *comp);
void		i_cal_component_set_comment	(ICalComponent *comp,
						 const gchar *v);
const gchar *	i_cal_component_get_comment	(ICalComponent *comp);
void		i_cal_component_set_uid		(ICalComponent *comp,
						 const gchar *v);
const gchar *	i_cal_component_get_uid		(ICalComponent *comp);
void		i_cal_component_set_relcalid	(ICalComponent *comp,
						 const gchar *v);
const gchar *	i_cal_component_get_relcalid	(ICalComponent *comp);
void		i_cal_component_set_description	(ICalComponent *comp,
						 const gchar *v);
const gchar *	i_cal_component_get_description	(ICalComponent *comp);
void		i_cal_component_set_location	(ICalComponent *comp,
						 const gchar *v);
const gchar *	i_cal_component_get_location	(ICalComponent *comp);
void		i_cal_component_set_sequence	(ICalComponent *comp,
						 gint v);
gint 		i_cal_component_get_sequence	(ICalComponent *comp);
ICalComponent *	i_cal_component_new_vcalendar	(void);
ICalComponent *	i_cal_component_new_vevent	(void);
ICalComponent *	i_cal_component_new_vtodo	(void);
ICalComponent *	i_cal_component_new_vjournal	(void);
ICalComponent *	i_cal_component_new_valarm	(void);
ICalComponent *	i_cal_component_new_vfreebusy	(void);
ICalComponent *	i_cal_component_new_vtimezone	(void);
ICalComponent *	i_cal_component_new_xstandard	(void);
ICalComponent *	i_cal_component_new_xdaylight	(void);
ICalComponent *	i_cal_component_new_vagenda	(void);
ICalComponent *	i_cal_component_new_vquery	(void);
void		i_cal_component_set_dtstart	(ICalComponent *comp,
						 ICalTimetype *v);
ICalTimetype *	i_cal_component_get_dtstart	(ICalComponent *comp);
void		i_cal_component_set_dtend	(ICalComponent *comp,
						 ICalTimetype *v);
ICalTimetype *	i_cal_component_get_dtend	(ICalComponent *comp);

G_END_DECLS

#endif /* I_CAL_COMPONENT_H */
