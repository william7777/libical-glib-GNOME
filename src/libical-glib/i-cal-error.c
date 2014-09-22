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

#include "i-cal-error.h"



/**
 * i_cal_error_stop_here:
 *
 * Since: 1.0
 *
 **/
void
i_cal_error_stop_here (void)
{
	icalerror_stop_here ();
}

/**
 * i_cal_error_crash_here:
 *
 * Shout out the errors to the compiler
 *
 * Since: 1.0
 *
 **/
void
i_cal_error_crash_here (void)
{
	icalerror_crash_here ();
}

/**
 * i_cal_errno_return:
 *
 * Returns: (transfer full): Return the error happened
 *
 * Return the error stored in the library. If no error, return ICAL_NO_ERROR.
 *
 * Since: 1.0
 *
 **/
ICalErrorEnum
i_cal_errno_return (void)
{
	return * (icalerrno_return ()) ;
}

/**
 * i_cal_error_clear_errno:
 *
 * Since: 1.0
 *
 **/
void
i_cal_error_clear_errno (void)
{
	icalerror_clear_errno ();
}

/**
 * i_cal_error_strerror:
 * @e: The #ICalErrorEnum to be translated
 *
 * Returns: (transfer none): The string representation of @e
 *
 * Translate the #ICalErrorEnum to the string representation
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_error_strerror (ICalErrorEnum e)
{
	return icalerror_strerror (e);
}

/**
 * i_cal_error_perror:
 *
 * Returns: (transfer none): The string representation of the current error
 *
 * Get the #ICalErrorEnum in the string representation. This method called the icalerrorno_return to get
 * the current error
 *
 * Since: 1.0
 *
 **/
const gchar *
i_cal_error_perror (void)
{
	return icalerror_perror ();
}

/**
 * i_cal_error_set_error_state:
 * @error: The error enum
 * @state: The error state
 *
 * Set the state to the corresponding error in the library.
 *
 * Since: 1.0
 *
 **/
void
i_cal_error_set_error_state (ICalErrorEnum error, 
                             ICalErrorState state)
{
	icalerror_set_error_state (error, state);
}

/**
 * i_cal_error_get_error_state:
 * @error: The error to be checked
 *
 * Returns: The state of the @error
 *
 * Get the state of an error
 *
 * Since: 1.0
 *
 **/
ICalErrorState
i_cal_error_get_error_state (ICalErrorEnum error)
{
	return icalerror_get_error_state (error);
}

/**
 * i_cal_error_supress:
 * @error: The error to be suppressed
 *
 * Returns: The error state suppressed
 *
 * Suppress the error
 *
 * Since: 1.0
 *
 **/
ICalErrorState
i_cal_error_supress (const gchar *error)
{
	g_return_val_if_fail (error != NULL, I_CAL_ERROR_DEFAULT);

	return icalerror_supress (error);
}

/**
 * i_cal_error_restore:
 * @error: The error to be restored
 * @es: The error state to be restored
 *
 * Restore the error to specified state
 *
 * Since: 1.0
 *
 **/
void
i_cal_error_restore (const gchar *error, 
                     ICalErrorState es)
{
	g_return_if_fail (error != NULL);

	icalerror_restore (error, es);
}


