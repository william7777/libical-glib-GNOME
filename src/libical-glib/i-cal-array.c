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

#include "i-cal-array.h"


G_DEFINE_TYPE (ICalArray, i_cal_array, I_CAL_TYPE_OBJECT)

static void
i_cal_array_class_init (ICalArrayClass *klass)
{	
	g_type_class_add_private (klass, sizeof (ICalArray));
}

static void
i_cal_array_init (ICalArray *self)
{
}

/**
 * i_cal_array_new_full: (skip)
 **/
ICalArray *
i_cal_array_new_full (icalarray *native, 
                      GObject *owner)
{
	ICalArray *object;
	object = g_object_new (I_CAL_ARRAY_TYPE, NULL);
	i_cal_object_construct ((ICalObject *)object,
		        	(gpointer) native,
		        	(GDestroyNotify) icalarray_free,
		        	FALSE,
		        	owner);
    							
	return object;
}

/**
 * i_cal_array_get_native_set_owner: (skip)
 **/
icalarray *
i_cal_array_get_native_set_owner (const ICalArray *object, 
                                  GObject *owner)
{
	icalarray *native_pointer;	
	if (owner != NULL)
		i_cal_object_set_owner ((ICalObject *)object, owner);
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	return native_pointer;
}

/**
 * i_cal_array_get_native_remove_owner: (skip)
 **/
icalarray *
i_cal_array_get_native_remove_owner (ICalArray *object)
{
	icalarray *native_pointer;	
	i_cal_object_remove_owner ((ICalObject *)object);
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	return native_pointer;
}

/**
 * i_cal_array_steal_native: (skip)
 **/
icalarray *
i_cal_array_steal_native (ICalArray *object)
{
	icalarray *native_pointer;
	native_pointer = (icalarray *)i_cal_object_steal_native ((ICalObject *)object);
    
	return native_pointer;
}

/**
 * i_cal_array_new:
 * @element_size: The size of the element of the array
 * @increment_size: The incremental size when the array is full
 *
 * Returns: (transfer full): The newly create #ICalArray with the properties set by @element_size and @increment_size
 *
 * Create a #ICalArray with the element size to be @element_size and increment size to be @increment_size
 *
 * Since: 1.0
 *
 **/
ICalArray *
i_cal_array_new (gint element_size, 
                 gint increment_size)
{
	return i_cal_array_new_full (icalarray_new (element_size, increment_size), NULL) ;
}

/**
 * i_cal_array_copy:
 * @array: (in): The #ICalArray to be cloned.
 *
 * Returns: (transfer full): The newly cloned #ICalArray with the same value as the @array
 *
 * Create a deep copy of #ICalArray with the same properties as the @array
 *
 * Since: 1.0
 *
 **/
ICalArray *
i_cal_array_copy (ICalArray *array)
{
	g_return_val_if_fail (I_CAL_IS_ARRAY (array), NULL);
	g_return_val_if_fail (array != NULL, NULL);

	return i_cal_array_new_full (icalarray_copy (i_cal_array_get_native_set_owner (array, NULL)), NULL) ;
}

/**
 * i_cal_array_free: (skip)
 * @array: (in): The #ICalArray to be freed.
 *
 * Free the #ICalArray
 *
 * Since: 1.0
 *
 **/
void
i_cal_array_free (ICalArray *array)
{
	g_return_if_fail (I_CAL_IS_ARRAY (array));
	g_return_if_fail (array != NULL);

	icalarray_free (i_cal_array_get_native_set_owner (array, NULL));
}

/**
 * i_cal_array_append:
 * @array: (inout): The #ICalArray to be appended.
 * @element: The element to be appended to the #ICalArray
 *
 * Append @element to the end of the array
 *
 * Since: 1.0
 *
 **/
void
i_cal_array_append (ICalArray *array, 
                    gconstpointer element)
{
	g_return_if_fail (I_CAL_IS_ARRAY (array));
	g_return_if_fail (array != NULL);

	icalarray_append (i_cal_array_get_native_set_owner (array, NULL), element);
}

/**
 * i_cal_array_remove_element_at:
 * @array: (inout): The #ICalArray to be modified.
 * @position: (in): The position in which the element will be removed from the array
 *
 * Remove the element at the @position from the array
 *
 * Since: 1.0
 *
 **/
void
i_cal_array_remove_element_at (ICalArray *array, 
                               gint position)
{
	g_return_if_fail (I_CAL_IS_ARRAY (array));
	g_return_if_fail (array != NULL);

	icalarray_remove_element_at (i_cal_array_get_native_set_owner (array, NULL), position);
}

/**
 * i_cal_array_element_at:
 * @array: The #ICalArray to be queried.
 * @position: The position the target element is located
 *
 * Returns: (transfer none) (allow-none): The element located at the @position in the @array
 *
 * Get the element located in the @position in the @array. NULL if position if out of bound
 *
 * Since: 1.0
 *
 **/
const void *
i_cal_array_element_at (ICalArray *array, 
                        gint position)
{
	g_return_val_if_fail (I_CAL_IS_ARRAY (array), NULL);
	g_return_val_if_fail (array != NULL, NULL);

	return icalarray_element_at (i_cal_array_get_native_set_owner (array, NULL), position);
}

/**
 * i_cal_array_sort:
 * @array: (inout): The #ICalArray to be sorted.
 * @compare: (scope call): The compare function which is used to sort the array
 *
 * Sort the @array using the sort function @compare
 *
 * Since: 1.0
 *
 **/
void
i_cal_array_sort (ICalArray *array, 
                  GCompareFunc compare)
{
	g_return_if_fail (I_CAL_IS_ARRAY (array));
	g_return_if_fail (array != NULL);

	icalarray_sort (i_cal_array_get_native_set_owner (array, NULL), compare);
}


