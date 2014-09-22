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

#include "i-cal-property.h"


G_DEFINE_TYPE (ICalProperty, i_cal_property, I_CAL_TYPE_OBJECT)

static void
i_cal_property_class_init (ICalPropertyClass *klass)
{	
	g_type_class_add_private (klass, sizeof (ICalProperty));
}

static void
i_cal_property_init (ICalProperty *self)
{
}

/**
 * i_cal_property_new_full: (skip)
 **/
ICalProperty *
i_cal_property_new_full (icalproperty *native, 
                         GObject *owner)
{
	ICalProperty *object;
	object = g_object_new (I_CAL_PROPERTY_TYPE, NULL);
	i_cal_object_construct ((ICalObject *)object,
		        	(gpointer) native,
		        	(GDestroyNotify) g_free,
		        	FALSE,
		        	owner);
    							
	return object;
}

/**
 * i_cal_property_get_native_set_owner: (skip)
 **/
icalproperty *
i_cal_property_get_native_set_owner (const ICalProperty *object, 
                                     GObject *owner)
{
	icalproperty *native_pointer;	
	if (owner != NULL)
		i_cal_object_set_owner ((ICalObject *)object, owner);
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	return native_pointer;
}

/**
 * i_cal_property_get_native_remove_owner: (skip)
 **/
icalproperty *
i_cal_property_get_native_remove_owner (ICalProperty *object)
{
	icalproperty *native_pointer;	
	i_cal_object_remove_owner ((ICalObject *)object);
	native_pointer = i_cal_object_get_native ((ICalObject *)object);
	return native_pointer;
}

/**
 * i_cal_property_steal_native: (skip)
 **/
icalproperty *
i_cal_property_steal_native (ICalProperty *object)
{
	icalproperty *native_pointer;
	native_pointer = (icalproperty *)i_cal_object_steal_native ((ICalObject *)object);
    
	return native_pointer;
}


