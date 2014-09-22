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

#include "i-cal-enums.h"



/**
 * i_cal_enum_reqstat_desc:
 * @stat: The #ICalRequestStatus to be translated
 *
 * Returns: The description of the @stat
 *
 * Return the descriptive text for a request status
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_enum_reqstat_desc (ICalRequestStatus stat)
{
	return icalenum_reqstat_desc (stat);
}

/**
 * i_cal_enum_reqstat_major:
 * @stat: The #ICalRequestStatus to be queried
 *
 * Returns: The major number for a request status
 *
 * Return the major number for a request status
 *
 * Since: 1.0
 *
 **/
gshort
i_cal_enum_reqstat_major (ICalRequestStatus stat)
{
	return icalenum_reqstat_major (stat);
}

/**
 * i_cal_enum_reqstat_minor:
 * @stat: The #ICalRequestStatus to be queried
 *
 * Returns: The minor number for a request status
 *
 * Return the minor number for a request status
 *
 * Since: 1.0
 *
 **/
gshort
i_cal_enum_reqstat_minor (ICalRequestStatus stat)
{
	return icalenum_reqstat_minor (stat);
}

/**
 * i_cal_enum_num_to_reqstat:
 * @major: The major number
 * @minor: The minor number
 *
 * Returns: The corresponding #ICalRequestStatus
 *
 * Return a request status for major/minor status numbers
 *
 * Since: 1.0
 *
 **/
ICalRequestStatus
i_cal_enum_num_to_reqstat (gshort major, 
                           gshort minor)
{
	return icalenum_num_to_reqstat (major, minor);
}

/**
 * i_cal_enum_reqstat_code_r:
 * @stat: The #ICalRequestStatus to be queried
 *
 * Returns: (transfer full): The code for a request status
 *
 * eturn the code for a request status
 *
 * Since: 1.0
 *
 **/
gchar *
i_cal_enum_reqstat_code_r (ICalRequestStatus stat)
{
	return icalenum_reqstat_code_r (stat);
}


