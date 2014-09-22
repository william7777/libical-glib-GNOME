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

#include "i-cal-duration-type.h"


G_DEFINE_TYPE (ICalDurationType, i_cal_duration_type, I_CAL_TYPE_OBJECT)

static void
i_cal_duration_type_class_init (ICalDurationTypeClass *klass)
{	
	g_type_class_add_private (klass, sizeof (ICalDurationType));
}

static void
i_cal_duration_type_init (ICalDurationType *self)
{
}

/**
 * i_cal_duration_type_new_full: (skip)
 **/
ICalDurationType *
i_cal_duration_type_new_full (struct icaldurationtype native)
{
	ICalDurationType *object;
	struct icaldurationtype *clone;
	object = g_object_new (I_CAL_DURATION_TYPE_TYPE, NULL);
	clone = g_new (struct icaldurationtype, 1);
	*clone = native;
	i_cal_object_construct ((ICalObject *)object,
		        	(gpointer) clone,
		        	(GDestroyNotify) g_free,
		        	FALSE,
		        	NULL);
    							
	return object;
}

/**
 * i_cal_duration_type_get_native_set_owner: (skip)
 **/
struct icaldurationtype
i_cal_duration_type_get_native_set_owner (const ICalDurationType *object)
{
	struct icaldurationtype *native_pointer;
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	
	if (native_pointer) {
		return *native_pointer;
	} else {
		return icaldurationtype_null_duration();
	}
}

/**
 * i_cal_duration_type_get_native_pointer_set_owner: (skip)
 **/
struct icaldurationtype *
i_cal_duration_type_get_native_pointer_set_owner (ICalDurationType *object)
{
	return i_cal_object_get_native ((ICalObject *)object);
}

/**
 * i_cal_duration_type_get_native_remove_owner: (skip)
 **/
struct icaldurationtype 
i_cal_duration_type_get_native_remove_owner (ICalDurationType *object)
{
	struct icaldurationtype *native_pointer;	
	i_cal_object_remove_owner ((ICalObject *)object);
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	
	if (native_pointer) {
		return *native_pointer;
	} else {
		return icaldurationtype_null_duration();
	}
}

/**
 * i_cal_duration_type_steal_native: (skip)
 **/
struct icaldurationtype 
i_cal_duration_type_steal_native (ICalDurationType *object)
{
	struct icaldurationtype *native_pointer;
	struct icaldurationtype native;
	native_pointer = (struct icaldurationtype *)i_cal_object_steal_native ((ICalObject *)object);
    
	if (native_pointer != NULL) {
		native = *native_pointer;
		g_free (native_pointer);
		return native;
	} else {
		return icaldurationtype_null_duration();
	}
}

/**
 * i_cal_duration_type_from_int:
 * @t: the duration in second
 *
 * Returns: (transfer full): The newly created #ICalDurationType
 *
 * Create a #ICalDurationType from the duration in second
 *
 * Since: 1.0
 *
 **/
ICalDurationType *
i_cal_duration_type_from_int (gint t)
{
	return i_cal_duration_type_new_full (icaldurationtype_from_int (t)) ;
}

/**
 * i_cal_duration_type_from_string:
 * @str: The string representation of the duration
 *
 * Returns: (transfer full): The newly created #ICalDurationType
 *
 * Create a #ICalDurationType from the duration in string
 *
 * Since: 1.0
 *
 **/
ICalDurationType *
i_cal_duration_type_from_string (const gchar *str)
{
	g_return_val_if_fail (str != NULL, NULL);

	return i_cal_duration_type_new_full (icaldurationtype_from_string (str)) ;
}

/**
 * i_cal_duration_type_as_int:
 * @duration: The #ICalDurationType to be converted
 *
 * Returns: The duration in second
 *
 * Convert the #ICalDurationType to the representation in second
 *
 * Since: 1.0
 *
 **/
gint
i_cal_duration_type_as_int (ICalDurationType *duration)
{
	g_return_val_if_fail (I_CAL_IS_DURATION_TYPE (duration), 0);
	g_return_val_if_fail (duration != NULL, 0);

	return icaldurationtype_as_int (i_cal_duration_type_get_native_set_owner (duration));
}

/**
 * i_cal_duration_type_as_ical_string_r:
 * @duration: The #ICalDurationType to be converted
 *
 * Returns: (transfer full): The duration in string
 *
 * Convert the #ICalDurationType to the representation in string
 *
 * Since: 1.0
 *
 **/
gchar *
i_cal_duration_type_as_ical_string_r (ICalDurationType *duration)
{
	g_return_val_if_fail (I_CAL_IS_DURATION_TYPE (duration), NULL);
	g_return_val_if_fail (duration != NULL, NULL);

	return icaldurationtype_as_ical_string_r (i_cal_duration_type_get_native_set_owner (duration));
}

/**
 * i_cal_duration_type_null_duration:
 *
 * Returns: (transfer full): The newly created #ICalDurationType
 *
 * Create a #ICalDurationType with all the fields to be zero
 *
 * Since: 1.0
 *
 **/
ICalDurationType *
i_cal_duration_type_null_duration (void)
{
	return i_cal_duration_type_new_full (icaldurationtype_null_duration ()) ;
}

/**
 * i_cal_duration_type_bad_duration:
 *
 * Returns: (transfer full): The newly created #ICalDurationType
 *
 * Create a bad #ICalDurationType
 *
 * Since: 1.0
 *
 **/
ICalDurationType *
i_cal_duration_type_bad_duration (void)
{
	return i_cal_duration_type_new_full (icaldurationtype_bad_duration ()) ;
}

/**
 * i_cal_duration_type_is_null_duration:
 * @duration: The #ICalDurationType to be checked
 *
 * Returns: 1 if @duration is the null_duration, 0 if not.
 *
 * Check whether the #ICalDurationType is the null_duration
 *
 * Since: 1.0
 *
 **/
gint
i_cal_duration_type_is_null_duration (ICalDurationType *duration)
{
	g_return_val_if_fail (I_CAL_IS_DURATION_TYPE (duration), 0);
	g_return_val_if_fail (duration != NULL, 0);

	return icaldurationtype_is_null_duration (i_cal_duration_type_get_native_set_owner (duration));
}

/**
 * i_cal_duration_type_is_bad_duration:
 * @duration: The #ICalDurationType to be checked
 *
 * Returns: 1 if @duration is the bad_duration, 0 if not.
 *
 * Check whether the #ICalDurationType is the bad_duration
 *
 * Since: 1.0
 *
 **/
gint
i_cal_duration_type_is_bad_duration (ICalDurationType *duration)
{
	g_return_val_if_fail (I_CAL_IS_DURATION_TYPE (duration), 0);
	g_return_val_if_fail (duration != NULL, 0);

	return icaldurationtype_is_bad_duration (i_cal_duration_type_get_native_set_owner (duration));
}


