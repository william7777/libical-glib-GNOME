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

#include "i-cal-tzutil.h"
#include "i-cal-component.h"



/**
 * ical_tzutil_get_zone_directory:
 *
 * Returns: (transfer none): The directory of the timezone files
 *
 * Get the directory of timezone files.
 *
 * Since: 1.0
 *
 **/
const gchar *
ical_tzutil_get_zone_directory (void)
{
	return icaltzutil_get_zone_directory ();
}

/**
 * i_cal_tzutil_fetch_timezone:
 * @location: The directory of the timezone files
 *
 * Returns: (transfer full): The timezone stored in the @location
 *
 * Fetch the timezone from a directory.
 *
 * Since: 1.0
 *
 **/
ICalComponent *
i_cal_tzutil_fetch_timezone (const gchar *location)
{
	g_return_val_if_fail (location != NULL, NULL);

	return i_cal_component_new_full (icaltzutil_fetch_timezone (location), NULL) ;
}


