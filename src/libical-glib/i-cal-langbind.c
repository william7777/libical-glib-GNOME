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

#include "i-cal-langbind.h"
#include "i-cal-component.h"
#include "i-cal-property.h"



/**
 * i_cal_langbind_new_array:
 * @size: The size of the array to be created.
 *
 * Returns: (transfer full): The newly created array
 *
 * Create a new array with specified size.
 *
 * Since: 1.0
 *
 **/
gint *
i_cal_langbind_new_array (gint size)
{
	return icallangbind_new_array (size);
}

/**
 * i_cal_langbind_free_array:
 * @array: (in) (transfer full): The array to be freed
 *
 * Free an array
 *
 * Since: 1.0
 *
 **/
void
i_cal_langbind_free_array (gint *array)
{
	g_return_if_fail (array != NULL);

	icallangbind_free_array (array);
}

/**
 * i_cal_langbind_access_array:
 * @array: The array to be accessed
 * @index: The index of element in the array to be accessed
 *
 * Returns: The element
 *
 * Array accesser
 *
 * Since: 1.0
 *
 **/
gint
i_cal_langbind_access_array (gint *array, 
                             gint index)
{
	g_return_val_if_fail (array != NULL, 0);

	return icallangbind_access_array (array, index);
}

/**
 * i_cal_langbind_get_first_parameter:
 * @prop: The #ICalProperty to be queried
 *
 * Returns: (allow-none) (transfer full): The next #ICalParameter in the #ICalProperty
 *
 * Get the first #ICalParameter in the #ICalProperty
 *
 * Since: 1.0
 *
 **/
ICalParameter *
i_cal_langbind_get_first_parameter (ICalProperty *prop)
{
	g_return_val_if_fail (I_CAL_IS_PROPERTY (prop), NULL);
	g_return_val_if_fail (prop != NULL, NULL);

	return icallangbind_get_first_parameter (i_cal_property_get_native_set_owner (prop, NULL));
}

/**
 * i_cal_langbind_get_next_parameter:
 * @prop: The #ICalProperty to be queried
 *
 * Returns: (allow-none) (transfer full): The next #ICalParameter in the #ICalProperty
 *
 * Get the next #ICalParameter in the#ICalProperty
 *
 * Since: 1.0
 *
 **/
ICalParameter *
i_cal_langbind_get_next_parameter (ICalProperty *prop)
{
	g_return_val_if_fail (I_CAL_IS_PROPERTY (prop), NULL);
	g_return_val_if_fail (prop != NULL, NULL);

	return icallangbind_get_next_parameter (i_cal_property_get_native_set_owner (prop, NULL));
}

/**
 * i_cal_langbind_get_first_property:
 * @c: The #ICalComponent to be queried.
 * @prop: The property name.
 *
 * Returns: (allow-none) (transfer full): The first #ICalProperty with the name @prop
 *
 * Get the first property with the target name.
 *
 * Since: 1.0
 *
 **/
ICalProperty *
i_cal_langbind_get_first_property (ICalComponent *c, 
                                   const gchar *prop)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (c), NULL);
	g_return_val_if_fail (c != NULL, NULL);
	g_return_val_if_fail (prop != NULL, NULL);

	return i_cal_property_new_full (icallangbind_get_first_property (i_cal_component_get_native_set_owner (c, NULL), prop), c) ;
}

/**
 * i_cal_langbind_get_next_property:
 * @c: The #ICalComponent to be queried.
 * @prop: The property name.
 *
 * Returns: (allow-none) (transfer full): The next #ICalProperty with the name @prop
 *
 * Get the next property with the target name.
 *
 * Since: 1.0
 *
 **/
ICalProperty *
i_cal_langbind_get_next_property (ICalComponent *c, 
                                  const gchar *prop)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (c), NULL);
	g_return_val_if_fail (c != NULL, NULL);
	g_return_val_if_fail (prop != NULL, NULL);

	return i_cal_property_new_full (icallangbind_get_next_property (i_cal_component_get_native_set_owner (c, NULL), prop), c) ;
}

/**
 * i_cal_langbind_get_first_component:
 * @c: The #ICalComponent to be queried.
 * @comp: The component name.
 *
 * Returns: (allow-none) (transfer full): The first #ICalComponent with the name @comp
 *
 * Get the first component with the target name.
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_langbind_get_first_component (ICalComponent *c, 
                                    const gchar *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (c), NULL);
	g_return_val_if_fail (c != NULL, NULL);
	g_return_val_if_fail (comp != NULL, NULL);

	return i_cal_component_new_full (icallangbind_get_first_component (i_cal_component_get_native_set_owner (c, NULL), comp), c) ;
}

/**
 * i_cal_langbind_get_next_component:
 * @c: The #ICalComponent to be queried.
 * @comp: The property name.
 *
 * Returns: (allow-none) (transfer full): The next #ICalComponent with the name @comp
 *
 * Get the next component with the target name.
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_langbind_get_next_component (ICalComponent *c, 
                                   const gchar *comp)
{
	g_return_val_if_fail (I_CAL_IS_COMPONENT (c), NULL);
	g_return_val_if_fail (c != NULL, NULL);
	g_return_val_if_fail (comp != NULL, NULL);

	return i_cal_component_new_full (icallangbind_get_next_property (i_cal_component_get_native_set_owner (c, NULL), comp), c) ;
}

/**
 * i_cal_langbind_property_eval_string_r:
 * @prop: The #ICalComponent to be translated.
 * @sep: The seperator.
 *
 * Returns: (transfer full): The sring representation of @prop
 *
 * Translate the #ICalProperty into the string representation.
 *
 * Since: 1.0
 *
 **/
gchar *
i_cal_langbind_property_eval_string_r (ICalProperty *prop, 
                                       gchar *sep)
{
	g_return_val_if_fail (I_CAL_IS_PROPERTY (prop), NULL);
	g_return_val_if_fail (prop != NULL, NULL);
	g_return_val_if_fail (sep != NULL, NULL);

	return icallangbind_property_eval_string_r (i_cal_property_get_native_set_owner (prop, NULL), sep);
}

/**
 * i_cal_langbind_string_to_open_flag:
 * @str: The string representation of the file open mode
 *
 * Returns: The enum representation of the file open mode
 *
 * Translate a string into the enum for the file open mode
 *
 * Since: 1.0
 *
 **/
gint
i_cal_langbind_string_to_open_flag (const gchar *str)
{
	g_return_val_if_fail (str != NULL, 0);

	return icallangbind_string_to_open_flag (str);
}

/**
 * i_cal_langbind_quote_as_ical_r:
 * @str: The string to be translated.
 *
 * Returns: (transfer full): The quote
 *
 * Encode a character string in ical format, esacpe certain characters, etc.
 *
 * Since: 1.0
 *
 **/
gchar *
i_cal_langbind_quote_as_ical_r (const gchar *str)
{
	g_return_val_if_fail (str != NULL, NULL);

	return icallangbind_quote_as_ical_r (str);
}


