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

#include "i-cal-attach.h"


G_DEFINE_TYPE (ICalAttach, i_cal_attach, I_CAL_TYPE_OBJECT)

static void
i_cal_attach_class_init (ICalAttachClass *klass)
{	
	g_type_class_add_private (klass, sizeof (ICalAttach));
}

static void
i_cal_attach_init (ICalAttach *self)
{
}

/**
 * i_cal_attach_new_full: (skip)
 **/
ICalAttach *
i_cal_attach_new_full (icalattach *native, 
                       GObject *owner)
{
	ICalAttach *object;
	object = g_object_new (I_CAL_ATTACH_TYPE, NULL);
	i_cal_object_construct ((ICalObject *)object,
		        	(gpointer) native,
		        	(GDestroyNotify) icalattach_unref,
		        	FALSE,
		        	owner);
    							
	return object;
}

/**
 * i_cal_attach_get_native_set_owner: (skip)
 **/
icalattach *
i_cal_attach_get_native_set_owner (const ICalAttach *object, 
                                   GObject *owner)
{
	icalattach *native_pointer;	
	if (owner != NULL)
		i_cal_object_set_owner ((ICalObject *)object, owner);
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	return native_pointer;
}

/**
 * i_cal_attach_get_native_remove_owner: (skip)
 **/
icalattach *
i_cal_attach_get_native_remove_owner (ICalAttach *object)
{
	icalattach *native_pointer;	
	i_cal_object_remove_owner ((ICalObject *)object);
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	return native_pointer;
}

/**
 * i_cal_attach_steal_native: (skip)
 **/
icalattach *
i_cal_attach_steal_native (ICalAttach *object)
{
	icalattach *native_pointer;
	native_pointer = (icalattach *)i_cal_object_steal_native ((ICalObject *)object);
    
	return native_pointer;
}

/**
 * i_cal_attach_new_from_url:
 * @url: (in): The url from which the object is created
 *
 * Returns: (out) (transfer full): The newly created #ICalAttach from the @url
 *
 * Create a new #ICalAttach from the url
 *
 * Since: 1.0
 *
 **/
ICalAttach *
i_cal_attach_new_from_url (const gchar *url)
{
	g_return_val_if_fail (url != NULL, NULL);

	return i_cal_attach_new_full (icalattach_new_from_url (url), NULL) ;
}

/**
 * i_cal_attach_new_from_data:
 * @data: (in): The data used to create the #ICalAttach
 * @free_fn: (scope call) (allow-none): The function used to free the data when the create #ICalAttach is detroyed.
 * @free_fn_data: (allow-none): The userdata used for the free function @free_fn
 *
 * Returns: (transfer full): The newly created #ICalAttach
 *
 * Create a new #ICalAttach from the data.
 *
 * Since: 1.0
 *
 **/
ICalAttach *
i_cal_attach_new_from_data (const gchar *data, 
                            GFunc free_fn, 
                            void *free_fn_data)
{
	g_return_val_if_fail (data != NULL, NULL);

	return i_cal_attach_new_full (icalattach_new_from_data (data, (icalattach_free_fn_t) (free_fn), free_fn_data), NULL) ;
}

/**
 * i_cal_attach_ref: (skip)
 * @attach: The #ICalAttach to be referenced by once
 *
 * Increase the ref counter by 1 for the @attach
 *
 * Since: 1.0
 *
 **/
void
i_cal_attach_ref (ICalAttach *attach)
{
	g_return_if_fail (I_CAL_IS_ATTACH (attach));
	g_return_if_fail (attach != NULL);

	icalattach_ref (i_cal_attach_get_native_set_owner (attach, NULL));
}

/**
 * i_cal_attach_unref: (skip)
 * @attach: The #ICalAttach to be unreferenced by once
 *
 * Decrese the ref counter by 1 for the @attach
 *
 * Since: 1.0
 *
 **/
void
i_cal_attach_unref (ICalAttach *attach)
{
	g_return_if_fail (I_CAL_IS_ATTACH (attach));
	g_return_if_fail (attach != NULL);

	icalattach_unref (i_cal_attach_get_native_set_owner (attach, NULL));
}

/**
 * i_cal_attach_get_is_url:
 * @attach: The #ICalAttach to be queried
 *
 * Returns: 1 if the @attach is built from url and 0 if not.
 *
 * Check whether the #ICalAttach is built from url
 *
 * Since: 1.0
 *
 **/
gint
i_cal_attach_get_is_url (ICalAttach *attach)
{
	g_return_val_if_fail (I_CAL_IS_ATTACH (attach), 0);
	g_return_val_if_fail (attach != NULL, 0);

	return icalattach_get_is_url (i_cal_attach_get_native_set_owner (attach, NULL));
}

/**
 * i_cal_attach_get_url:
 * @attach: The #ICalAttach to be queried
 *
 * Returns: (allow-none) (transfer none): The url component of the @attach. NULL if it is built from data or there is an error.
 *
 * Get the url if the #ICalAttach is built from the url. NULL if else.
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_attach_get_url (ICalAttach *attach)
{
	g_return_val_if_fail (I_CAL_IS_ATTACH (attach), NULL);
	g_return_val_if_fail (attach != NULL, NULL);

	return icalattach_get_url (i_cal_attach_get_native_set_owner (attach, NULL));
}

/**
 * i_cal_attach_get_data:
 * @attach: The #ICalAttach to be queried
 *
 * Returns: (type utf8) (allow-none) (transfer none): The data component of the @attach. NULL if it is built from url or there is an error.
 *
 * Get the data if the #ICalAttach is built from the data. NULL if else.
 *
 * Since: 1.0
 *
 **/
guchar *
i_cal_attach_get_data (ICalAttach *attach)
{
	g_return_val_if_fail (I_CAL_IS_ATTACH (attach), NULL);
	g_return_val_if_fail (attach != NULL, NULL);

	return icalattach_get_data (i_cal_attach_get_native_set_owner (attach, NULL));
}


