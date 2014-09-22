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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "i-cal-component.h"
#include "i-cal-property.h"
#include "i-cal-timetype.h"
#include "i-cal-enums.h"


G_DEFINE_TYPE (ICalComponent, i_cal_component, I_CAL_TYPE_OBJECT)

static void
i_cal_component_class_init (ICalComponentClass *klass)
{	
	g_type_class_add_private (klass, sizeof (ICalComponent));
}

static void
i_cal_component_init (ICalComponent *self)
{
}

/**
 * i_cal_component_new_full: (skip)
 **/
ICalComponent *
i_cal_component_new_full (icalcomponent *native, 
                          GObject *owner)
{
	ICalComponent *object;
	object = g_object_new (I_CAL_COMPONENT_TYPE, NULL);
	i_cal_object_construct ((ICalObject *)object,
		        	(gpointer) native,
		        	(GDestroyNotify) icalcomponent_free,
		        	FALSE,
		        	owner);
    							
	return object;
}

/**
 * i_cal_component_get_native_set_owner: (skip)
 **/
icalcomponent *
i_cal_component_get_native_set_owner (const ICalComponent *object, 
                                      GObject *owner)
{
	icalcomponent *native_pointer;	
	if (owner != NULL)
		i_cal_object_set_owner ((ICalObject *)object, owner);
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	return native_pointer;
}

/**
 * i_cal_component_get_native_remove_owner: (skip)
 **/
icalcomponent *
i_cal_component_get_native_remove_owner (ICalComponent *object)
{
	icalcomponent *native_pointer;	
	i_cal_object_remove_owner ((ICalObject *)object);
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	return native_pointer;
}

/**
 * i_cal_component_steal_native: (skip)
 **/
icalcomponent *
i_cal_component_steal_native (ICalComponent *object)
{
	icalcomponent *native_pointer;
	native_pointer = (icalcomponent *)i_cal_object_steal_native ((ICalObject *)object);
    
	return native_pointer;
}

/**
 * i_cal_component_new:
 * @kind: The #ICalComponentKind.
 *
 * Returns: (transfer full): The newly created #ICalComponent.
 *
 * Create a new #ICalComponent with specific type.
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new (ICalComponentKind kind)
{
	return i_cal_component_new_full (icalcomponent_new (kind), NULL) ;
}

/**
 * i_cal_component_new_clone:
 * @component: The #ICalComponent to be created.
 *
 * Returns: (transfer full): The newly deeply cloned #ICalComponent.
 *
 * Deeply clone a #ICalComponent.
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_clone (ICalComponent *component)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (component), NULL);
	g_return_val_if_fail (component != NULL, NULL);

	return i_cal_component_new_full (icalcomponent_new_clone (i_cal_component_get_native_set_owner (component, NULL)), NULL) ;
}

/**
 * i_cal_component_new_from_string:
 * @str: The string used to create #ICalComponent.
 *
 * Returns: (transfer full): The newly created #ICalComponent based on @str.
 *
 * Create a new #ICalComponent based on a string.
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_from_string (const gchar *str)
{
	g_return_val_if_fail (str != NULL, NULL);

	return i_cal_component_new_full (icalcomponent_new_from_string (str), NULL) ;
}

/**
 * i_cal_component_new_x:
 * @x_name: The name of x property.
 *
 * Returns: (transfer full): The newly created #ICalComponent.
 *
 * Create a new #ICalComponent based on name of x property.
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_x (const gchar *x_name)
{
	g_return_val_if_fail (x_name != NULL, NULL);

	return i_cal_component_new_full (icalcomponent_new_x (x_name), NULL) ;
}

/**
 * i_cal_component_free:
 * @component: The #ICalComponent to be freed.
 *
 * Free a #ICalComponent.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_free (ICalComponent *component)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (component));
	g_return_if_fail (component != NULL);

	icalcomponent_free (i_cal_component_get_native_set_owner (component, NULL));
}

/**
 * i_cal_component_as_ical_string_r:
 * @component: The #ICalComponent to be converted.
 *
 * Returns: (transfer full): The string representation of #ICalComponent.
 *
 * Convert a #ICalComponent to a string.
 *
 * Since: 1.0
 *
 **/
gchar *
i_cal_component_as_ical_string_r (ICalComponent *component)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (component), NULL);
	g_return_val_if_fail (component != NULL, NULL);

	return icalcomponent_as_ical_string_r (i_cal_component_get_native_set_owner (component, NULL));
}

/**
 * i_cal_component_is_valid:
 * @component: The #ICalComponent to be checked.
 *
 * Returns: 1 if yes, 0 if not.
 *
 * Check whether #ICalComponent is valid.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_component_is_valid (ICalComponent *component)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (component), 0);
	g_return_val_if_fail (component != NULL, 0);

	return icalcomponent_is_valid (i_cal_component_get_native_set_owner (component, NULL));
}

/**
 * i_cal_component_isa:
 * @component: The #ICalComponent to be checked.
 *
 * Returns: A #ICalComponentKind.
 *
 * Get the type of #ICalComponent.
 *
 * Since: 1.0
 *
 **/
ICalComponentKind
i_cal_component_isa (ICalComponent *component)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (component), I_CAL_NO_COMPONENT);
	g_return_val_if_fail (component != NULL, I_CAL_NO_COMPONENT);

	return icalcomponent_isa (i_cal_component_get_native_set_owner (component, NULL));
}

/**
 * i_cal_component_isa_component:
 * @component: The #ICalComponent to be checked.
 *
 * Returns: 1 if yes, 0 if not.
 *
 * Check whether the native part of #ICalComponent is icalcomponent.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_component_isa_component (ICalComponent *component)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (component), 0);
	g_return_val_if_fail (component != NULL, 0);

	return icalcomponent_isa_component (i_cal_component_get_native_set_owner (component, NULL));
}

/**
 * i_cal_component_add_property:
 * @component: A #ICalComponent.
 * @property: A #ICalProperty.
 *
 * Add a #ICalProperty into #ICalComponent.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_add_property (ICalComponent *component, 
                              ICalProperty *property)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (component));
	g_return_if_fail (component != NULL);
	g_return_if_fail (I_CAL_IS_PROPERTY (property));
	g_return_if_fail (property != NULL);

	icalcomponent_add_property (i_cal_component_get_native_set_owner (component, (GObject *)property), i_cal_property_get_native_set_owner (property, NULL));
}

/**
 * i_cal_component_remove_property:
 * @component: A #ICalComponent.
 * @property: A #ICalProperty.
 *
 * Remove #ICalProperty from #ICalComponent.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_remove_property (ICalComponent *component, 
                                 ICalProperty *property)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (component));
	g_return_if_fail (component != NULL);
	g_return_if_fail (I_CAL_IS_PROPERTY (property));
	g_return_if_fail (property != NULL);

	icalcomponent_remove_property (i_cal_component_get_native_remove_owner (component), i_cal_property_get_native_set_owner (property, NULL));
}

/**
 * i_cal_component_count_properties:
 * @component: The #ICalComponent.
 * @kind: A #ICalPropertyKind.
 *
 * Returns: The number of #ICalProperties.
 *
 * Count the #ICalProperty in #ICalComponent.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_component_count_properties (ICalComponent *component, 
                                  ICalPropertyKind kind)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (component), 0);
	g_return_val_if_fail (component != NULL, 0);

	return icalcomponent_count_properties (i_cal_component_get_native_set_owner (component, NULL), kind);
}

/**
 * i_cal_component_get_current_property:
 * @component: A #ICalComponent.
 *
 * Returns: (transfer full): The current #ICalProperty.
 *
 * Get the current #ICalProperty in #ICalComponent.
 *
 * Since: 1.0
 *
 **/
ICalProperty *
i_cal_component_get_current_property (ICalComponent *component)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (component), NULL);
	g_return_val_if_fail (component != NULL, NULL);

	return i_cal_property_new_full (icalcomponent_get_current_property (i_cal_component_get_native_set_owner (component, NULL)), NULL) ;
}

/**
 * i_cal_component_get_first_property:
 * @component: A #ICalComponent.
 * @kind: A #ICalPropertyKind.
 *
 * Returns: (transfer full): The first #ICalProperty.
 *
 * Get the first #ICalProperty with specific kind in #ICalComponent.
 *
 * Since: 1.0
 *
 **/
ICalProperty *
i_cal_component_get_first_property (ICalComponent *component, 
                                    ICalPropertyKind kind)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (component), NULL);
	g_return_val_if_fail (component != NULL, NULL);

	return i_cal_property_new_full (icalcomponent_get_first_property (i_cal_component_get_native_set_owner (component, NULL), kind), NULL) ;
}

/**
 * i_cal_component_get_next_property:
 * @component: A #ICalComponent.
 * @kind: A #ICalPropertyKind.
 *
 * Returns: (transfer full): The next #ICalProperty.
 *
 * Get the next #ICalProperty with specific kind in #ICalComponent.
 *
 * Since: 1.0
 *
 **/
ICalProperty *
i_cal_component_get_next_property (ICalComponent *component, 
                                   ICalPropertyKind kind)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (component), NULL);
	g_return_val_if_fail (component != NULL, NULL);

	return i_cal_property_new_full (icalcomponent_get_next_property (i_cal_component_get_native_set_owner (component, NULL), kind), NULL) ;
}

/**
 * i_cal_component_get_inner:
 * @comp: A #ICalComponent.
 *
 * Returns: (transfer full): The first VEVENT, VTODO or VJOURNAL sub-component.
 *
 * Return the first VEVENT, VTODO or VJOURNAL sub-component of cop, or comp if it is one of those types.
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_get_inner (ICalComponent *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (comp), NULL);
	g_return_val_if_fail (comp != NULL, NULL);

	return i_cal_component_new_full (icalcomponent_get_inner (i_cal_component_get_native_set_owner (comp, NULL)), NULL) ;
}

/**
 * i_cal_component_add_component:
 * @parent: A #ICalComponent.
 * @child: A child #ICalComponent.
 *
 * Add a #ICalComponent into another #ICalComponent as a child component.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_add_component (ICalComponent *parent, 
                               ICalComponent *child)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (parent));
	g_return_if_fail (parent != NULL);
	g_return_if_fail (I_CAL_IS_COMPONENT (child));
	g_return_if_fail (child != NULL);

	icalcomponent_add_component (i_cal_component_get_native_set_owner (parent, NULL), i_cal_component_get_native_set_owner (child, (GObject *)parent));
}

/**
 * i_cal_component_remove_component:
 * @parent: A #ICalComponent.
 * @child: A child #ICalComponent.
 *
 * Remove a child #ICalComponent from another #ICalComponent.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_remove_component (ICalComponent *parent, 
                                  ICalComponent *child)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (parent));
	g_return_if_fail (parent != NULL);
	g_return_if_fail (I_CAL_IS_COMPONENT (child));
	g_return_if_fail (child != NULL);

	icalcomponent_remove_component (i_cal_component_get_native_remove_owner (parent), i_cal_component_get_native_set_owner (child, NULL));
}

/**
 * i_cal_component_count_components:
 * @component: The #ICalComponent to be checked.
 * @kind: The target #ICalComponentKind
 *
 * Returns: The count of child #ICalComponent in the parent one.
 *
 * Count the child #ICalComponent with the target kind in the parent one.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_component_count_components (ICalComponent *component, 
                                  ICalComponentKind kind)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (component), 0);
	g_return_val_if_fail (component != NULL, 0);

	return icalcomponent_count_components (i_cal_component_get_native_set_owner (component, NULL), kind);
}

/**
 * i_cal_component_merge_component:
 * @comp: The #ICalComponent.
 * @comp_to_merge: (in): A #ICalComponent. After merged it will not exist any more.
 *
 * This takes 2 VCALENDAR components and merges the second one into the first, resolving any problems with
 * conflicting TZIDs. comp_to_merge will no longer exist after calling this function.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_merge_component (ICalComponent *comp, 
                                 ICalComponent *comp_to_merge)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (comp));
	g_return_if_fail (comp != NULL);
	g_return_if_fail (I_CAL_IS_COMPONENT (comp_to_merge));
	g_return_if_fail (comp_to_merge != NULL);

	icalcomponent_merge_component (i_cal_component_get_native_set_owner (comp, NULL), i_cal_component_steal_native (comp_to_merge));
}

/**
 * i_cal_component_get_current_component:
 * @component: A #ICalComponent.
 *
 * Returns: (transfer full): The current #ICalComponent.
 *
 * Get the current #ICalComponent in #ICalComponent.
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_get_current_component (ICalComponent *component)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (component), NULL);
	g_return_val_if_fail (component != NULL, NULL);

	return i_cal_component_new_full (icalcomponent_get_current_component (i_cal_component_get_native_set_owner (component, NULL)), NULL) ;
}

/**
 * i_cal_component_get_first_component:
 * @component: A #ICalComponent.
 * @kind: A #ICalComponentKind.
 *
 * Returns: (transfer full): The first #ICalComponent.
 *
 * Get the first #ICalComponent with specific kind in #ICalComponent.
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_get_first_component (ICalComponent *component, 
                                     ICalComponentKind kind)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (component), NULL);
	g_return_val_if_fail (component != NULL, NULL);

	return i_cal_component_new_full (icalcomponent_get_first_component (i_cal_component_get_native_set_owner (component, NULL), kind), NULL) ;
}

/**
 * i_cal_component_get_next_component:
 * @component: A #ICalComponent.
 * @kind: A #ICalComponentKind.
 *
 * Returns: (transfer full): The next #ICalComponent.
 *
 * Get the next #ICalComponent with specific kind in #ICalComponent.
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_get_next_component (ICalComponent *component, 
                                    ICalComponentKind kind)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (component), NULL);
	g_return_val_if_fail (component != NULL, NULL);

	return i_cal_component_new_full (icalcomponent_get_next_component (i_cal_component_get_native_set_owner (component, NULL), kind), NULL) ;
}

/**
 * i_cal_component_check_restrictions:
 * @comp: A #ICalComponent
 *
 * Returns: 1 if valid, 0 if not.
 *
 * Check whether #ICalComponent is valid in terms of restrictions.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_component_check_restrictions (ICalComponent *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (comp), 0);
	g_return_val_if_fail (comp != NULL, 0);

	return icalcomponent_check_restrictions (i_cal_component_get_native_set_owner (comp, NULL));
}

/**
 * i_cal_component_count_errors:
 * @comp: A #ICalComponent
 *
 * Returns: The count of errors.
 *
 * Count the number of errors in #ICalComponent.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_component_count_errors (ICalComponent *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (comp), 0);
	g_return_val_if_fail (comp != NULL, 0);

	return icalcomponent_count_errors (i_cal_component_get_native_set_owner (comp, NULL));
}

/**
 * i_cal_component_strip_errors:
 * @comp: A #ICalComponent
 *
 * Remove all X-LIC-ERROR properties.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_strip_errors (ICalComponent *comp)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (comp));
	g_return_if_fail (comp != NULL);

	icalcomponent_strip_errors (i_cal_component_get_native_set_owner (comp, NULL));
}

/**
 * i_cal_component_convert_errors:
 * @comp: A #ICalComponent
 *
 * Convert some X-LIC-ERROR properties into RETURN-STATUS properties.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_convert_errors (ICalComponent *comp)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (comp));
	g_return_if_fail (comp != NULL);

	icalcomponent_convert_errors (i_cal_component_get_native_set_owner (comp, NULL));
}

/**
 * i_cal_component_kind_is_valid:
 * @kind: A #ICalComponentKind.
 *
 * Returns: 1 if @kind id a #ICalComponent but not the I_CAL_NO_COMPONENT, 0 if not.
 *
 * Check if a #ICalComponentKind is valid.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_component_kind_is_valid (const ICalComponentKind kind)
{
	return icalcomponent_kind_is_valid (kind);
}

/**
 * i_cal_component_string_to_kind:
 * @string: A string.
 *
 * Returns: A #ICalComponentKind
 *
 * Convert a string to a #ICalComponentKind.
 *
 * Since: 1.0
 *
 **/
ICalComponentKind
i_cal_component_string_to_kind (const gchar *string)
{
	g_return_val_if_fail (string != NULL, I_CAL_NO_COMPONENT);

	return icalcomponent_string_to_kind (string);
}

/**
 * i_cal_component_kind_to_string:
 * @kind: A #ICalComponentKind.
 *
 * Returns: (transfer none): The string representation of @kind.
 *
 * Convert a #ICalComponentKind to a string.
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_component_kind_to_string (ICalComponentKind kind)
{
	return icalcomponent_kind_to_string (kind);
}

/**
 * i_cal_component_get_first_real_component:
 * @c: A VCOMPONENT type of #ICalComponent.
 *
 * Returns: (transfer full): A reference to the first VEVENT, VTODO or VJOURNAL
 *
 * For VCOMPONENT: Return a reference to the first VEVENT, VTODO or VJOURNAL.
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_get_first_real_component (ICalComponent *c)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (c), NULL);
	g_return_val_if_fail (c != NULL, NULL);

	return i_cal_component_new_full (icalcomponent_get_first_real_component (i_cal_component_get_native_set_owner (c, NULL)), (GObject *)c) ;
}

/**
 * i_cal_component_set_summary:
 * @comp: A #ICalComponent.
 * @v: A string representing summary.
 *
 * Set the summary of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_set_summary (ICalComponent *comp, 
                             const gchar *v)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (comp));
	g_return_if_fail (comp != NULL);
	g_return_if_fail (v != NULL);

	icalcomponent_set_summary (i_cal_component_get_native_set_owner (comp, NULL), v);
}

/**
 * i_cal_component_get_summary:
 * @comp: A #ICalComponent.
 *
 * Returns: (transfer none): The summary of @comp.
 *
 * Get the summary of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_component_get_summary (ICalComponent *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (comp), NULL);
	g_return_val_if_fail (comp != NULL, NULL);

	return icalcomponent_get_summary (i_cal_component_get_native_set_owner (comp, NULL));
}

/**
 * i_cal_component_set_comment:
 * @comp: A #ICalComponent.
 * @v: A string representing comment.
 *
 * Set the comment of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_set_comment (ICalComponent *comp, 
                             const gchar *v)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (comp));
	g_return_if_fail (comp != NULL);
	g_return_if_fail (v != NULL);

	icalcomponent_set_comment (i_cal_component_get_native_set_owner (comp, NULL), v);
}

/**
 * i_cal_component_get_comment:
 * @comp: A #ICalComponent.
 *
 * Returns: (transfer none): The comment of @comp.
 *
 * Get the comment of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_component_get_comment (ICalComponent *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (comp), NULL);
	g_return_val_if_fail (comp != NULL, NULL);

	return icalcomponent_get_comment (i_cal_component_get_native_set_owner (comp, NULL));
}

/**
 * i_cal_component_set_uid:
 * @comp: A #ICalComponent.
 * @v: A string representing uid.
 *
 * Set the uid of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_set_uid (ICalComponent *comp, 
                         const gchar *v)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (comp));
	g_return_if_fail (comp != NULL);
	g_return_if_fail (v != NULL);

	icalcomponent_set_uid (i_cal_component_get_native_set_owner (comp, NULL), v);
}

/**
 * i_cal_component_get_uid:
 * @comp: A #ICalComponent.
 *
 * Returns: (transfer none): The uid of @comp.
 *
 * Get the uid of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_component_get_uid (ICalComponent *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (comp), NULL);
	g_return_val_if_fail (comp != NULL, NULL);

	return icalcomponent_get_uid (i_cal_component_get_native_set_owner (comp, NULL));
}

/**
 * i_cal_component_set_relcalid:
 * @comp: A #ICalComponent.
 * @v: A string representing relcalid.
 *
 * Set the relcalid of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_set_relcalid (ICalComponent *comp, 
                              const gchar *v)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (comp));
	g_return_if_fail (comp != NULL);
	g_return_if_fail (v != NULL);

	icalcomponent_set_relcalid (i_cal_component_get_native_set_owner (comp, NULL), v);
}

/**
 * i_cal_component_get_relcalid:
 * @comp: A #ICalComponent.
 *
 * Returns: (transfer none): The relcalid of @comp.
 *
 * Get the relcalid of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_component_get_relcalid (ICalComponent *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (comp), NULL);
	g_return_val_if_fail (comp != NULL, NULL);

	return icalcomponent_get_relcalid (i_cal_component_get_native_set_owner (comp, NULL));
}

/**
 * i_cal_component_set_description:
 * @comp: A #ICalComponent.
 * @v: A string representing description.
 *
 * Set the description of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_set_description (ICalComponent *comp, 
                                 const gchar *v)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (comp));
	g_return_if_fail (comp != NULL);
	g_return_if_fail (v != NULL);

	icalcomponent_set_description (i_cal_component_get_native_set_owner (comp, NULL), v);
}

/**
 * i_cal_component_get_description:
 * @comp: A #ICalComponent.
 *
 * Returns: (transfer none): The description of @comp.
 *
 * Get the description of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_component_get_description (ICalComponent *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (comp), NULL);
	g_return_val_if_fail (comp != NULL, NULL);

	return icalcomponent_get_description (i_cal_component_get_native_set_owner (comp, NULL));
}

/**
 * i_cal_component_set_location:
 * @comp: A #ICalComponent.
 * @v: A string representing location.
 *
 * Set the location of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_set_location (ICalComponent *comp, 
                              const gchar *v)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (comp));
	g_return_if_fail (comp != NULL);
	g_return_if_fail (v != NULL);

	icalcomponent_set_location (i_cal_component_get_native_set_owner (comp, NULL), v);
}

/**
 * i_cal_component_get_location:
 * @comp: A #ICalComponent.
 *
 * Returns: (transfer none): The location of @comp.
 *
 * Get the location of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_component_get_location (ICalComponent *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (comp), NULL);
	g_return_val_if_fail (comp != NULL, NULL);

	return icalcomponent_get_location (i_cal_component_get_native_set_owner (comp, NULL));
}

/**
 * i_cal_component_set_sequence:
 * @comp: A #ICalComponent.
 * @v: The sequence number.
 *
 * Set the sequence of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_set_sequence (ICalComponent *comp, 
                              gint v)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (comp));
	g_return_if_fail (comp != NULL);

	icalcomponent_set_sequence (i_cal_component_get_native_set_owner (comp, NULL), v);
}

/**
 * i_cal_component_get_sequence:
 * @comp: A #ICalComponent.
 *
 * Returns: The sequence of @comp.
 *
 * Get the sequence of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
gint
i_cal_component_get_sequence (ICalComponent *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (comp), 0);
	g_return_val_if_fail (comp != NULL, 0);

	return icalcomponent_get_sequence (i_cal_component_get_native_set_owner (comp, NULL));
}

/**
 * i_cal_component_new_vcalendar:
 *
 * Returns: (transfer full): The newly created #ICalComponent.
 *
 * Create a #ICalComponent with the type to be vcalendar
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_vcalendar (void)
{
	return i_cal_component_new_full (icalcomponent_new_vcalendar (), NULL) ;
}

/**
 * i_cal_component_new_vevent:
 *
 * Returns: (transfer full): The newly created #ICalComponent.
 *
 * Create a #ICalComponent with the type to be vevent
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_vevent (void)
{
	return i_cal_component_new_full (icalcomponent_new_vevent (), NULL) ;
}

/**
 * i_cal_component_new_vtodo:
 *
 * Returns: (transfer full): The newly created #ICalComponent.
 *
 * Create a #ICalComponent with the type to be vtodo
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_vtodo (void)
{
	return i_cal_component_new_full (icalcomponent_new_vtodo (), NULL) ;
}

/**
 * i_cal_component_new_vjournal:
 *
 * Returns: (transfer full): The newly created #ICalComponent.
 *
 * Create a #ICalComponent with the type to be vjournal
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_vjournal (void)
{
	return i_cal_component_new_full (icalcomponent_new_vjournal (), NULL) ;
}

/**
 * i_cal_component_new_valarm:
 *
 * Returns: (transfer full): The newly created #ICalComponent.
 *
 * Create a #ICalComponent with the type to be valarm
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_valarm (void)
{
	return i_cal_component_new_full (icalcomponent_new_valarm (), NULL) ;
}

/**
 * i_cal_component_new_vfreebusy:
 *
 * Returns: (transfer full): The newly created #ICalComponent.
 *
 * Create a #ICalComponent with the type to be vfreebusy
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_vfreebusy (void)
{
	return i_cal_component_new_full (icalcomponent_new_vfreebusy (), NULL) ;
}

/**
 * i_cal_component_new_vtimezone:
 *
 * Returns: (transfer full): The newly created #ICalComponent.
 *
 * Create a #ICalComponent with the type to be vtimezone
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_vtimezone (void)
{
	return i_cal_component_new_full (icalcomponent_new_vtimezone (), NULL) ;
}

/**
 * i_cal_component_new_xstandard:
 *
 * Returns: (transfer full): The newly created #ICalComponent.
 *
 * Create a #ICalComponent with the type to be xstandard
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_xstandard (void)
{
	return i_cal_component_new_full (icalcomponent_new_xstandard (), NULL) ;
}

/**
 * i_cal_component_new_xdaylight:
 *
 * Returns: (transfer full): The newly created #ICalComponent.
 *
 * Create a #ICalComponent with the type to be xdaylight
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_xdaylight (void)
{
	return i_cal_component_new_full (icalcomponent_new_xdaylight (), NULL) ;
}

/**
 * i_cal_component_new_vagenda:
 *
 * Returns: (transfer full): The newly created #ICalComponent.
 *
 * Create a #ICalComponent with the type to be vagenda
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_vagenda (void)
{
	return i_cal_component_new_full (icalcomponent_new_vagenda (), NULL) ;
}

/**
 * i_cal_component_new_vquery:
 *
 * Returns: (transfer full): The newly created #ICalComponent.
 *
 * Create a #ICalComponent with the type to be vquery
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_component_new_vquery (void)
{
	return i_cal_component_new_full (icalcomponent_new_vquery (), NULL) ;
}

/**
 * i_cal_component_set_dtstart:
 * @comp: A #ICalComponent.
 * @v: A #ICalTimetype.
 *
 * Set the dtstart of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_set_dtstart (ICalComponent *comp, 
                             ICalTimetype *v)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (comp));
	g_return_if_fail (comp != NULL);
	g_return_if_fail (I_CAL_IS_TIMETYPE (v));
	g_return_if_fail (v != NULL);

	icalcomponent_set_dtstart (i_cal_component_get_native_set_owner (comp, NULL), i_cal_timetype_get_native_set_owner (v));
}

/**
 * i_cal_component_get_dtstart:
 * @comp: A #ICalComponent.
 *
 * Returns: (transfer full): A #ICalTimetype.
 *
 * Get the dtstart of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
ICalTimetype *
i_cal_component_get_dtstart (ICalComponent *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (comp), NULL);
	g_return_val_if_fail (comp != NULL, NULL);

	return i_cal_timetype_new_full (icalcomponent_get_dtstart (i_cal_component_get_native_set_owner (comp, NULL))) ;
}

/**
 * i_cal_component_set_dtend:
 * @comp: A #ICalComponent.
 * @v: A #ICalTimetype.
 *
 * Set the dtend of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
void
i_cal_component_set_dtend (ICalComponent *comp, 
                           ICalTimetype *v)
{
	g_return_if_fail (I_CAL_IS_COMPONENT (comp));
	g_return_if_fail (comp != NULL);
	g_return_if_fail (I_CAL_IS_TIMETYPE (v));
	g_return_if_fail (v != NULL);

	icalcomponent_set_dtend (i_cal_component_get_native_set_owner (comp, NULL), i_cal_timetype_get_native_set_owner (v));
}

/**
 * i_cal_component_get_dtend:
 * @comp: A #ICalComponent.
 *
 * Returns: (transfer full): A #ICalTimetype.
 *
 * Get the dtend of the #ICalComponent.
 *
 * Since: 1.0
 *
 **/
ICalTimetype *
i_cal_component_get_dtend (ICalComponent *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (comp), NULL);
	g_return_val_if_fail (comp != NULL, NULL);

	return i_cal_timetype_new_full (icalcomponent_get_dtend (i_cal_component_get_native_set_owner (comp, NULL))) ;
}


