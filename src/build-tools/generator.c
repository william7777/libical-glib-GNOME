/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * Copyright (C) 2015 William Yu <williamyu@gnome.org>
 *
 * This library is free software: you can redistribute it and/or modify it
 * under the terms of version 2.1. of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "generator.h"

static const gchar *templates_dir = NULL;
static const gchar *apis_dir = NULL;

static FILE *
open_file (const gchar * dir, const gchar *filename)
{
	gchar *path;
	FILE *tmpl;

	path = g_build_filename (dir, filename, NULL);
	g_return_val_if_fail (path != NULL, NULL);

	tmpl = fopen (path, "rb");
	if (!tmpl)
		fprintf (stderr, "Failed to open '%s'\n", path);

	g_free (path);

	return tmpl;
}

gchar *
get_source_method_comment (Method *method)
{
	GList *iter_list;
	GList *jter;
	Parameter *para;
	gchar *anno;
	gchar *buffer;	
	gchar *res;
	gchar *comment_line;
	gint iter;
	gint len;
	gint count;
	gint cursor;
	gchar *full_flag;
	gchar *full_comment;
	
	g_return_val_if_fail (method != NULL, NULL);
	
	res = g_strdup ("/**");
	buffer = g_strconcat (res, "\n * ", method->name, ":", NULL);
	g_free (res);
	res = buffer;

	for (iter_list = g_list_first (method->annotations); iter_list != NULL; iter_list = g_list_next (iter_list)) {
		anno = (gchar *)iter_list->data;
		buffer = g_strconcat (res, " (", anno, ")", NULL);
		g_free (res);
		res = buffer;
	}
	
	/* Processing the parameters */
	if (method->parameters != NULL) {
		for (iter_list = g_list_first (method->parameters); iter_list != NULL; iter_list = g_list_next (iter_list)) {
			para = (Parameter *)iter_list->data;

			/* Handling the special case in which the parameter's comment is fully specified */
			full_flag = g_strdup ("FULL:");
			for (iter = 0; iter < strlen (full_flag) && iter < strlen (para->comment); iter++) {
				if (full_flag[iter] != para->comment[iter]) {
					break;
				}
			}

			if (iter == strlen (full_flag)) {
				full_comment = g_new (gchar, strlen (para->comment) - strlen (full_flag) + 1);
				stpcpy (full_comment, para->comment + strlen(full_flag));
				buffer = g_strconcat (res, "\n * ", full_comment, NULL);
				g_free (res);
				res = buffer;
				g_free (full_comment);
			} else {
				buffer = g_strconcat (res, "\n * @", NULL);
				g_free (res);
				res = buffer;

				para = (Parameter *)iter_list->data;
				buffer = g_strconcat (res, para->name,  NULL);
				g_free (res);
				res = buffer;

				for (jter = g_list_first (para->annotations); jter != NULL; jter = g_list_next (jter)) {
					anno = (gchar *)jter->data;
					if (jter == g_list_first (para->annotations)) {
						buffer = g_strconcat (res, ": (", anno, ")", NULL);
					} else {
						buffer = g_strconcat (res, " (", anno, ")", NULL);
					}
					g_free (res);
					res = buffer;
				}

				if (para->comment != NULL) {
					buffer = g_strconcat (res, ": ", para->comment, NULL);
					g_free (res);
					res = buffer;
				}
			}
			g_free (full_flag);
		}
	}
	
	/* Processing general comment */
	if (method->comment != NULL) {
		comment_line = g_new (gchar, BUFFER_SIZE);
		*comment_line = '\0';
		len = strlen (method->comment);
		count = 0;
		g_stpcpy (comment_line, "\n *\n * ");
		for (iter = 0; iter < len; iter++) {
			if (count >= COMMENT_LINE_LENGTH && method->comment[iter] == ' ') {
				g_stpcpy (comment_line + strlen (comment_line), "\n *");
				count = -1;
			}

			cursor = strlen (comment_line);
			comment_line[cursor] = method->comment[iter];
			comment_line[cursor+1] = '\0';

			count++;
		}
		
		buffer = g_strconcat (res, comment_line, NULL);
		g_free (res);
		g_free (comment_line);
		res = buffer;
	}
	
	/* Processing return */
	if (method->ret != NULL) {
		buffer = g_strconcat (res, "\n *\n * Returns", NULL);
		g_free (res);
		res = buffer;

		for (jter = g_list_first (method->ret->annotations); jter != NULL; jter = g_list_next (jter)) {
			anno = (gchar *)jter->data;
			if (jter == g_list_first (method->ret->annotations)) {
				buffer = g_strconcat (res, ": (", anno, ")", NULL);
			} else {
				buffer = g_strconcat (res, " (", anno, ")", NULL);
			}
			g_free (res);
			res = buffer;
		}

		if (method->ret->comment != NULL) {
			buffer = g_strconcat (res, ": ", method->ret->comment, NULL);
			g_free (res);
			res = buffer;
		}
	}

	/* Processing the since */
	buffer = g_strconcat (res, "\n *\n * Since: ", method->since, "\n *", NULL);
	g_free (res);
	res = buffer;
	
	buffer = g_strconcat (res, "\n **/",NULL);
	g_free (res);
	res = buffer;
	buffer = NULL;
	return res;
}

gchar *
get_upper_camel_from_lower_snake (const gchar *lowerSnake)
{
	gchar *buffer;
	gchar *ret;
	guint len;
	guint i;
	
	g_return_val_if_fail (lowerSnake != NULL && *lowerSnake != '\0', NULL);

	buffer = g_new (gchar, BUFFER_SIZE);
	buffer[0] = toupper (lowerSnake[0]);
	buffer[1] = '\0';
	for (i = 1; i < strlen (lowerSnake); i++) {
		if (lowerSnake[i] == '_') {
			len = strlen (buffer);
			buffer[len] = toupper (lowerSnake[++i]);
			buffer[len+1] = '\0';
		} else {
			len = strlen (buffer);
			buffer[len] = lowerSnake[i];
			buffer[len+1] = '\0';
		}
	}
	
	ret = g_new (gchar, strlen (buffer) + 1);
	for (i = 0; i < strlen (buffer); i++) {
		ret[i] = buffer[i];
	}
	ret[i] = '\0';
	g_free (buffer);
	return ret;
}

gchar *
get_upper_snake_from_lower_snake (const gchar *lowerSnake)
{
	gchar *ret;
	gchar *dest;
	guint i;
	
	g_return_val_if_fail (lowerSnake != NULL && *lowerSnake != '\0', NULL);
	
	ret = g_new (gchar, BUFFER_SIZE);
	ret[0] = '\0';
	
	for (i = 0; i < strlen (lowerSnake); i++) {
		if (lowerSnake[i] == '_') {
			ret[i] = '_';
			ret[i+1] = '\0';
		} else {
			ret[i] = toupper (lowerSnake[i]);
			ret[i+1] = '\0';
		}		
	}
	
	dest = g_new (gchar , strlen (ret)+1);
	for (i = 0; i < strlen (ret); i++) {
		dest[i] = ret[i];
	}
	dest[i] = '\0';
	g_free (ret);
	return dest;
}

gchar *
get_upper_snake_from_upper_camel (const gchar *upperCamel)
{
	gchar *lowerSnake;
	gchar *upperSnake;
	
	g_return_val_if_fail (upperCamel != NULL, NULL);
	lowerSnake = get_lower_snake_from_upper_camel (upperCamel);	
	upperSnake = get_upper_snake_from_lower_snake (lowerSnake);
	g_free (lowerSnake);
	return upperSnake;
}

gchar *
get_lower_snake_from_upper_camel (const gchar *upperCamel)
{
	gchar *buffer;
	gchar *dest;
	guint i;
	guint len;
	
	g_return_val_if_fail (upperCamel != NULL && *upperCamel != '\0', NULL);
	
	buffer = g_new (gchar, BUFFER_SIZE);
	*buffer = '\0';
	
	for (i = 0; i < strlen (upperCamel); i++) {
		if (isupper (upperCamel[i]) && i != 0) {
			len = strlen (buffer);
			buffer[len] = '_';
			buffer[len+1] = tolower (upperCamel[i]);
			buffer[len+2] = '\0';
		} else {
			len = strlen (buffer);
			buffer[len] = tolower (upperCamel[i]);
			buffer[len+1] = '\0';
		}
	}
	
	dest = g_strdup (buffer);
	g_free (buffer);
	return dest;
}

gchar *
get_lower_train_from_lower_snake (const gchar *lowerSnake)
{
	int i;
	gchar *ret;
	
	g_return_val_if_fail (lowerSnake != NULL && *lowerSnake != '\0', NULL);
	
	ret = g_strdup (lowerSnake);
	for (i = 0; i < strlen (lowerSnake); i++) {
		if (lowerSnake[i] == '_')
			ret[i] = '-';
	}
	
	return ret;
}

gchar *
get_lower_train_from_upper_camel (const gchar *upperCamel)
{
	int i;
	gchar *ret;
	int len;
	
	g_return_val_if_fail (upperCamel != NULL && *upperCamel != '\0', NULL);
			
	ret = get_lower_snake_from_upper_camel (upperCamel);
	len = strlen (ret);
	for (i = 0; i < len; i++) {
		if (ret[i] == '_')
			ret[i] = '-';
	}
	
	return ret;
}

void
generate_header_method_get_type (FILE *out, Structure *structure)
{
	gchar *upperCamel;
	gchar *lowerSnake;
	Method *get_type;
	
	g_return_if_fail (out != NULL && structure != NULL);
	upperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
	lowerSnake = get_lower_snake_from_upper_camel (upperCamel);
	g_free (upperCamel);
	
	get_type = method_new();
	get_type->ret = ret_new();
	get_type->ret->type = g_strdup ("GType");
	get_type->name = g_strconcat (lowerSnake, "_get_type", NULL);
	g_free (lowerSnake);
	generate_header_method_proto (out, get_type);
	method_free (get_type);
}

void
generate_header_method_new_full (FILE *out, Structure *structure)
{
	gchar *upperCamel;
	gchar *lowerSnake;
	Parameter *para;	
	Method *new_full;
	
	g_return_if_fail (out != NULL && structure != NULL);
	
	new_full = method_new();
	upperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
	lowerSnake = get_lower_snake_from_upper_camel (upperCamel);
	new_full->ret = ret_new();
	new_full->ret->type = g_strconcat (upperCamel, " *", NULL);
	g_free (upperCamel);
	
	new_full->name = g_strconcat (lowerSnake, "_new_full", NULL);
	g_free (lowerSnake);
	
	para = parameter_new ();
	if (structure->isBare) {
		para->type = g_strdup (structure->native);
	} else {
		para->type = g_strconcat (structure->native, " *", NULL);
	}
	para->name = g_strdup ("native");
	new_full->parameters = g_list_append (new_full->parameters, para);
	para = NULL;
	
	if (structure->isBare == FALSE) {
		para = parameter_new ();
		para->type = g_strdup ("GObject *");
		para->name = g_strdup ("owner");
		new_full->parameters = g_list_append (new_full->parameters, para);
		para = NULL;
	}
	
	if (structure->isPossibleGlobal == TRUE) {
		para = parameter_new ();
		para->type = g_strdup ("gboolean");
		para->name = g_strdup ("is_global_memory");
		new_full->parameters = g_list_append (new_full->parameters, para);
		para = NULL;
	}
	
	generate_header_method_proto (out, new_full);
	method_free (new_full);
	
}

gchar *
get_source_method_proto_new_full (Structure *structure)
{
	gchar *upperCamel;
	gchar *lowerSnake;
	Parameter *para;	
	Method *new_full;
	gchar *res;
	
	g_return_val_if_fail (structure != NULL, NULL);
	
	new_full = method_new();
	upperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
	lowerSnake = get_lower_snake_from_upper_camel (upperCamel);
	
	new_full->ret = ret_new();
	new_full->ret->type = g_strconcat (upperCamel, " *", NULL);
	g_free (upperCamel);
	
	new_full->name = g_strconcat (lowerSnake, "_new_full", NULL);
	g_free (lowerSnake);
	
	para = parameter_new ();
	if (structure->isBare) {
		para->type = g_strdup (structure->native);
	} else {
		para->type = g_strconcat (structure->native, " *", NULL);
	}
	para->name = g_strdup ("native");
	new_full->parameters = g_list_append (new_full->parameters, para);
	para = NULL;
	
	if (structure->isBare == FALSE) {
		para = parameter_new ();
		para->type = g_strdup ("GObject *");
		para->name = g_strdup ("owner");
		new_full->parameters = g_list_append (new_full->parameters, para);
		para = NULL;
	}
	
	if (structure->isPossibleGlobal == TRUE) {
		para = parameter_new ();
		para->type = g_strdup ("gboolean");
		para->name = g_strdup ("is_global_memory");
		new_full->parameters = g_list_append (new_full->parameters, para);
		para = NULL;
	}
	
	res = get_source_method_proto (new_full);
	method_free (new_full);
	return res;
}

gchar *
get_source_method_proto_set_owner (Structure *structure)
{
	gchar *upperCamel;
	gchar *lowerSnake;
	Parameter *para;	
	Method *set_owner;
	gchar *res;
	
	g_return_val_if_fail (structure != NULL, NULL);
	upperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
	lowerSnake = get_lower_snake_from_upper_camel (upperCamel);
	set_owner = method_new();
	
	set_owner->name = g_strconcat (lowerSnake, "_set_owner", NULL);
	g_free (lowerSnake);
	
	para = parameter_new ();
	para->type = g_strconcat ("const ", upperCamel, " *", NULL);
	g_free (upperCamel);
	para->name = g_strdup ("object");
	set_owner->parameters = g_list_append (set_owner->parameters, para);
	para = NULL;
	
	para = parameter_new ();
	para->type = g_strdup ("GObject *");
	para->name = g_strdup ("owner");
	set_owner->parameters = g_list_append (set_owner->parameters, para);
	para = NULL;
	
	res = get_source_method_proto (set_owner);
	method_free (set_owner);
	return res;
}

gchar *
get_source_method_proto_set_native (Structure *structure)
{
	gchar *upperCamel;
	gchar *lowerSnake;
	Parameter *para;	
	Method *set_native;
	gchar *res;
	
	g_return_val_if_fail (structure != NULL, NULL);
	upperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
	lowerSnake = get_lower_snake_from_upper_camel (upperCamel);
	set_native = method_new();
	set_native->name = g_strconcat (lowerSnake, "_set_native", NULL);
	g_free (lowerSnake);
	
	para = parameter_new ();
	para->type = g_strconcat (upperCamel, " *", NULL);
	g_free (upperCamel);
	para->name = g_strdup ("object");
	set_native->parameters = g_list_append (set_native->parameters, para);
	para = NULL;
	
	para = parameter_new ();	
	para->type = g_strdup ("gpointer");
	para->name = g_strdup ("native");
	set_native->parameters = g_list_append (set_native->parameters, para);
	para = NULL;
	
	res = get_source_method_proto (set_native);
	method_free (set_native);
	return res;
}

gchar *
get_source_method_proto_set_is_global (Structure *structure)
{
	gchar *upperCamel;
	gchar *lowerSnake;
	Parameter *para;	
	Method *set_is_global;
	gchar *res;
	
	g_return_val_if_fail (structure != NULL, NULL);
	upperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
	lowerSnake = get_lower_snake_from_upper_camel (upperCamel);
	set_is_global = method_new();
	set_is_global->name = g_strconcat (lowerSnake, "_set_is_global", NULL);
	g_free (lowerSnake);
	
	para = parameter_new ();
	para->type = g_strconcat (upperCamel, " *", NULL);
	g_free (upperCamel);
	para->name = g_strdup ("object");
	set_is_global->parameters = g_list_append (set_is_global->parameters, para);
	para = NULL;
	
	para = parameter_new ();	
	para->type = g_strdup ("gboolean");
	para->name = g_strdup ("is_global_memory");
	set_is_global->parameters = g_list_append (set_is_global->parameters, para);
	para = NULL;
	
	res = get_source_method_proto (set_is_global);
	method_free (set_is_global);
	return res;
}

gchar *
get_source_method_proto_set_property (Structure *structure)
{
	gchar *upperCamel;
	gchar *lowerSnake;
	Parameter *para;	
	Method *set_property;
	gchar *res;
	
	g_return_val_if_fail (structure != NULL, NULL);
	upperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
	lowerSnake = get_lower_snake_from_upper_camel (upperCamel);
	g_free (upperCamel);
	set_property = method_new();
	set_property->name = g_strconcat (lowerSnake, "_set_property", NULL);
	g_free (lowerSnake);
	
	para = parameter_new ();
	para->type = g_strdup ("GObject *");
	para->name = g_strdup ("object");
	set_property->parameters = g_list_append (set_property->parameters, para);
	para = NULL;
	
	para = parameter_new ();	
	para->type = g_strdup ("guint");
	para->name = g_strdup ("property_id");
	set_property->parameters = g_list_append (set_property->parameters, para);
	para = NULL;
	
	para = parameter_new ();	
	para->type = g_strdup ("const GValue *");
	para->name = g_strdup ("value");
	set_property->parameters = g_list_append (set_property->parameters, para);
	para = NULL;
	
	para = parameter_new ();	
	para->type = g_strdup ("GParamSpec *");
	para->name = g_strdup ("pspec");
	set_property->parameters = g_list_append (set_property->parameters, para);
	para = NULL;
	
	res = get_source_method_proto (set_property);
	method_free (set_property);
	return res;
}

gchar *
get_source_method_proto_get_property (Structure *structure)
{
	gchar *upperCamel;
	gchar *lowerSnake;
	Parameter *para;	
	Method *get_property;
	gchar *res;
	
	g_return_val_if_fail (structure != NULL, NULL);
	upperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
	lowerSnake = get_lower_snake_from_upper_camel (upperCamel);
	g_free (upperCamel);
	get_property = method_new();
	get_property->name = g_strconcat (lowerSnake, "_get_property", NULL);
	g_free (lowerSnake);
	
	para = parameter_new ();
	para->type = g_strdup ("GObject *");
	para->name = g_strdup ("object");
	get_property->parameters = g_list_append (get_property->parameters, para);
	para = NULL;
	
	para = parameter_new ();	
	para->type = g_strdup ("guint");
	para->name = g_strdup ("property_id");
	get_property->parameters = g_list_append (get_property->parameters, para);
	para = NULL;
	
	para = parameter_new ();	
	para->type = g_strdup ("GValue *");
	para->name = g_strdup ("value");
	get_property->parameters = g_list_append (get_property->parameters, para);
	para = NULL;
	
	para = parameter_new ();	
	para->type = g_strdup ("GParamSpec *");
	para->name = g_strdup ("pspec");
	get_property->parameters = g_list_append (get_property->parameters, para);
	para = NULL;
	
	res = get_source_method_proto (get_property);
	method_free (get_property);
	return res;
}

void
generate_header_method_protos (FILE *out, Structure *structure)
{
	GList *iter;
	Method *method;
	gchar *typeName;
	FILE * privateHeader;
	gchar *privateHeaderComment;
	
	privateHeader = NULL;
	typeName = g_strconcat (structure->nameSpace, structure->name, NULL);
	privateHeaderComment = g_strconcat ("/* Private header for ", typeName, " */\n", NULL);

	if (structure->native != NULL) {
		/** Open or create the private header file if it does not exist.
		 * Create the forward declaration.
		 * Create the new_full method in it.
		 */
		privateHeader = fopen (PRIVATE_HEADER, "ab+");
		fwrite (privateHeaderComment, sizeof (gchar), strlen (privateHeaderComment), privateHeader);
		fwrite ("typedef struct _", sizeof (gchar), strlen ("typedef struct _"), privateHeader);
		fwrite (typeName, sizeof (gchar), strlen (typeName), privateHeader);
		fputc (' ', privateHeader);
		fwrite (typeName, sizeof (gchar), strlen (typeName), privateHeader);
		fputc (';', privateHeader);
		fputc ('\n', privateHeader);
		generate_header_method_new_full (privateHeader, structure);

		generate_header_method_get_type (out, structure);
	}
	
	for (iter = g_list_first (structure->methods); iter != NULL; iter = g_list_next (iter)) {
		method = (Method *)iter->data;

		if (g_strcmp0 (method->kind, "private") == 0) {
			/* This checks whether there was method declared in private header already. If not, the forward declaration is needed. */
			if (privateHeader == NULL) {
				privateHeader = fopen (PRIVATE_HEADER, "ab+");
				fwrite ("typedef struct _", sizeof (gchar), strlen ("typedef struct _"), privateHeader);
				fwrite (typeName, sizeof (gchar), strlen (typeName), privateHeader);
				fputc (' ', privateHeader);
				fwrite (typeName, sizeof (gchar), strlen (typeName), privateHeader);
				fputc (';', privateHeader);
				fputc ('\n', privateHeader);

			}
			generate_header_method_proto (privateHeader, method);
		} else {
			generate_header_method_proto (out, method);
		}
	}

	g_free (typeName);

	if (privateHeader != NULL) {
		fclose (privateHeader);
		privateHeader = NULL;
	}
}

void
generate_header_method_proto (FILE *out, Method *method)
{
	GList *iter_list;
	Parameter *para;
	gint count;
	gchar *buffer;
	gint iter;
	gint len;
	
	buffer = g_new (gchar, BUFFER_SIZE);
	*buffer = '\0';
	
	/* Generate the method return */
	if (method->ret == NULL) {
		fwrite ("void", sizeof (char), strlen ("void"), out);
		for (iter = 0; iter < RET_TAB_COUNT; iter++) {
			fwrite ("\t", sizeof (char), strlen ("\t"), out);
		}
	} else {
		count = strlen (method->ret->type)/TAB_SIZE;
		*buffer = '\0';
		if (count >= RET_TAB_COUNT) {
			buffer[0] = '\n';
			buffer[1] = '\0';
			count = 0;
		}
		for (iter = count; iter < RET_TAB_COUNT; iter++) {
			len = strlen (buffer);
			buffer[len] = '\t';
			buffer[len+1] = '\0';
		}
		
		fwrite (method->ret->type, sizeof (char), strlen (method->ret->type), out);
		if (method->ret->type[strlen (method->ret->type) - 1] != '*')
			fputc (' ', out);
		fwrite (buffer, sizeof (gchar), strlen (buffer), out);
	}
	
	/* Generate the method name */
	count = strlen (method->name)/TAB_SIZE;
	*buffer = '\0';
	if (count >= METHOD_NAME_TAB_COUNT) {
		buffer[0] = '\n';
		buffer[1] = '\0';
		count = 0;
		for (iter = count; iter < RET_TAB_COUNT + METHOD_NAME_TAB_COUNT; iter++) {
			len = strlen (buffer);
			buffer[len] = '\t';
			buffer[len+1] = '\0';
		}
	} else {
		for (iter = count; iter < METHOD_NAME_TAB_COUNT; iter++) {
			len = strlen (buffer);
			buffer[len] = '\t';
			buffer[len+1] = '\0';
		}
	}

	fwrite (method->name, sizeof (char), strlen (method->name), out);
	fwrite (buffer, sizeof (gchar), strlen (buffer), out);
	
	/* Generate all the parameters */
	for (iter = 0; iter < RET_TAB_COUNT + METHOD_NAME_TAB_COUNT; iter++) {
		buffer[iter] = '\t';
	}
	buffer[iter] = '\0';
	
	if (method->parameters == NULL) {
		fwrite ("(void);", sizeof (gchar), strlen ("(void);"), out);
	} else {
		for (iter_list = g_list_first (method->parameters); iter_list != NULL; iter_list = g_list_next (iter_list)) {
			para = (Parameter *)iter_list->data;
			if (iter_list == g_list_first (method->parameters))
				fwrite ("(", sizeof (char), strlen ("("), out);
			else {
				fwrite (",\n", sizeof (char), strlen (",\n"), out);
				fwrite (buffer, sizeof (gchar), strlen (buffer), out);
				fputc (' ', out);
			}
			fwrite ((char *)para->type, sizeof (char), strlen (para->type), out);
			if (para->type[strlen (para->type) - 1] != '*')
				fputc (' ', out);
			fwrite ((char *)para->name, sizeof (char), strlen (para->name), out);
		}
		fwrite (");", sizeof (char), strlen (");"), out);
	}
	fputc ('\n', out);
	g_free (buffer);
}

void
generate_code_from_template (FILE *in, FILE *out, Structure *structure, GHashTable *table)
{
	gchar c;
	gchar *buffer;
	gint count;
	gchar last;
	gint len;
	GList *iter;
	gchar *method;
	gchar *val;

	g_return_if_fail (in != NULL && out != NULL && structure != NULL && table != NULL);

	buffer = g_new (gchar, BUFFER_SIZE);
	*buffer = '\0';

	while ((c = fgetc (in)) != EOF) {
		if (c == '$') {
			if ((c = fgetc (in)) != '{' && c != '^') {
				printf ("The following char is not {");
				return;
			}

			if (c == '^') {
				count = 1;
				last = '\0';
				while (!((c = fgetc (in)) == '$' && last == '^' && count == 1)) {
					if (c == '^' && last == '$') {
						++count;
						last = '\0';
					}else if (c == '$' && last == '^') {
						--count;
						last = '\0';
					} else {
						last = c;
					}
					len = strlen (buffer);
					buffer[len] = c;
					buffer[len+1] = '\0';
				}
				if (strlen (buffer) > 0)
					buffer[strlen(buffer)-1] = '\0';
				generate_conditional (out, structure, buffer, table);
			} else {
				while ((c = fgetc (in)) != '}') {
					len = strlen (buffer);
					buffer[len] = c;
					buffer[len+1] = '\0';
				}

				if (g_strcmp0 (buffer, "source") == 0) {
					for (iter = g_list_first (structure->methods); iter != NULL; iter = g_list_next (iter)) {
						method = get_source_method_body ((Method *)iter->data, structure->nameSpace);
						fwrite (method, sizeof (gchar), strlen (method), out);
						if (iter != g_list_last (structure->methods)) {
							fwrite ("\n\n", sizeof (gchar), strlen ("\n\n"), out);
						}
						g_free (method);
					}
				} else if (g_strcmp0 (buffer, "enums") == 0) {
					generate_header_enums (out, structure);
				} else if (g_strcmp0 (buffer, "protos") == 0) {
					generate_header_method_protos (out, structure);
				} else if (g_strcmp0 (buffer, "headerIncludes") == 0) {
					generate_header_includes (out, structure);
				} else if (g_strcmp0 (buffer, "sourceIncludes") == 0) {
					generate_source_includes (out, structure);
				} else if (g_strcmp0 (buffer, "forward_declaration") == 0) {
					generate_header_forward_declaration (out, structure);
				} else if (g_strcmp0 (buffer, "header_declaration") == 0) {
					generate_header_header_declaration (out, structure);
				} else if (g_hash_table_contains (table, buffer)) {
					val = g_hash_table_lookup (table, buffer);
					fwrite (val, sizeof (gchar), strlen (val), out);
					val = NULL;
				} else if (g_strcmp0 (buffer, "structure_boilerplate") == 0) {
					if (structure->native != NULL)
						generate_header_structure_boilerplate (out, structure, table);
				} else if (g_hash_table_contains (table, buffer)) {
					val = g_hash_table_lookup (table, buffer);
					fwrite (val, sizeof (gchar), strlen (val), out);
					val = NULL;
				} else if (g_strcmp0 (buffer, "source_boilerplate") == 0) {
					if (structure->native != NULL)
						generate_source_structure_boilerplate (out, structure, table);
				} else {
					printf ("The string %s is not recognized, please check the template\n", buffer);
					fflush (NULL);
					return;
				}
			}
			buffer[0] = '\0';
		} else {
			fputc (c, out);
		}
	}

	g_free (buffer);
}

void
generate_header (FILE *out, Structure *structure, GHashTable* table)
{
	FILE *in;
	
	g_return_if_fail (out != NULL && structure != NULL && table != NULL);

	in = open_file (templates_dir, HEADER_TEMPLATE);
	generate_code_from_template (in, out, structure, table);
	fclose (in);
}

void
generate_header_structure_boilerplate (FILE *out, Structure *structure, GHashTable* table)
{
	FILE *in;
	
	g_return_if_fail (out != NULL && structure != NULL && table != NULL);
	
	in = open_file (templates_dir, HEADER_STRUCTURE_BOILERPLATE_TEMPLATE);
	generate_code_from_template (in, out, structure, table);
	fclose (in);
}

void
generate_header_includes (FILE *out, Structure *structure)
{
	gchar *typeName;
	Structure *parentStructure;
	gchar *lowerTrain;
	gchar *upperCamel;
	gchar *ownUpperCamel;
	gchar *includeName;
	GHashTable *includeNames;
	GHashTableIter iter_table;
	gpointer key;
	gpointer value;
	gchar *kind;
	GList *iter;

	g_return_if_fail (out != NULL && structure != NULL);

	for (iter = g_list_first (structure->includes); iter != NULL; iter = g_list_next (iter)) {
		includeName = (gchar *)iter->data;
		fwrite ("#include <", sizeof (gchar), strlen ("#include <"), out);
		fwrite (includeName, sizeof (gchar), strlen (includeName), out);
		fwrite (">\n", sizeof (gchar), strlen (">\n"), out);
	}

	fwrite ("#include <", sizeof (gchar), strlen ("#include <"), out);
	fwrite (COMMON_HEADER, sizeof (gchar), strlen (COMMON_HEADER), out);
	fwrite (".h>\n", sizeof (gchar), strlen (".h>\n"), out);

	g_return_if_fail (out != NULL && structure != NULL);

	includeNames = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);

	upperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
	lowerTrain = get_lower_train_from_upper_camel (upperCamel);
	g_free (upperCamel);

	for (g_hash_table_iter_init (&iter_table, structure->dependencies); g_hash_table_iter_next (&iter_table, &key, &value);) {
		typeName = (gchar *)key;
		if (g_hash_table_contains (type2structure, typeName)) {
			parentStructure = g_hash_table_lookup (type2structure, typeName);
			upperCamel = g_strconcat (parentStructure->nameSpace, parentStructure->name, NULL);
			ownUpperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
			if (g_strcmp0 (upperCamel, ownUpperCamel) == 0) {
				g_free (upperCamel);
				g_free (ownUpperCamel);
				continue;
			}

			kind = g_strdup (g_hash_table_lookup(type2kind, typeName));
			if (g_strcmp0 (kind, "enum") != 0) {
				g_free (kind);
				g_free (upperCamel);
				g_free (ownUpperCamel);
				continue;
			}
			g_free (kind);
			lowerTrain = get_lower_train_from_upper_camel (upperCamel);
			g_free (upperCamel);
			g_hash_table_insert (includeNames, lowerTrain, NULL);
			lowerTrain = NULL;
		}
	}

	for (g_hash_table_iter_init (&iter_table, includeNames); g_hash_table_iter_next (&iter_table, &key, &value);) {
		includeName = (gchar *)key;
		fwrite ("#include <libical-glib/", sizeof (gchar), strlen ("#include <libical-glib/"), out);
		fwrite (includeName, sizeof (gchar), strlen (includeName), out);
		fwrite (".h>\n", sizeof (gchar), strlen (".h>\n"), out);
	}
	g_hash_table_destroy (includeNames);
}

void
generate_source_includes (FILE *out, Structure *structure)
{
	gchar *typeName;
	Structure *parentStructure;
	gchar *lowerTrain;
	gchar *upperCamel;
	gchar *ownUpperCamel;
	gchar *includeName;
	GHashTable *includeNames;
	GHashTableIter iter_table;
	gpointer key;
	gpointer value;
	
	g_return_if_fail (out != NULL && structure != NULL);
	
	includeNames = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);
		
	upperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
	lowerTrain = get_lower_train_from_upper_camel (upperCamel);
	g_free (upperCamel);
	fwrite ("#include <libical-glib/", sizeof (gchar), strlen ("#include <libical-glib/"), out);
	fwrite (lowerTrain, sizeof (gchar), strlen (lowerTrain), out);
	fwrite (".h>\n", sizeof (gchar), strlen (".h>\n"), out);
	g_free (lowerTrain);

	fwrite ("#include <libical-glib/", sizeof (gchar), strlen ("#include <libical-glib/"), out);
	fwrite (PRIVATE_HEADER, sizeof (gchar), strlen (PRIVATE_HEADER), out);
	fwrite (">\n", sizeof (gchar), strlen (">\n"), out);
		
	for (g_hash_table_iter_init (&iter_table, structure->dependencies); g_hash_table_iter_next (&iter_table, &key, &value);) {
		typeName = (gchar *)key;
		if (g_hash_table_contains (type2structure, typeName)) {
			parentStructure = g_hash_table_lookup (type2structure, typeName);
			upperCamel = g_strconcat (parentStructure->nameSpace, parentStructure->name, NULL);
			ownUpperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
			if (g_strcmp0 (upperCamel, ownUpperCamel) == 0) {
				g_free (upperCamel);
				g_free (ownUpperCamel);
				continue;
			}
			lowerTrain = get_lower_train_from_upper_camel (upperCamel);
			g_free (upperCamel);
			g_hash_table_insert (includeNames, lowerTrain, NULL);
			lowerTrain = NULL;
		}
	}
	
	for (g_hash_table_iter_init (&iter_table, includeNames); g_hash_table_iter_next (&iter_table, &key, &value);) {
		includeName = (gchar *)key;
		fwrite ("#include <libical-glib/", sizeof (gchar), strlen ("#include <libical-glib/"), out);
		fwrite (includeName, sizeof (gchar), strlen (includeName), out);
		fwrite (".h>\n", sizeof (gchar), strlen (".h>\n"), out);
	}

	fputc ('\n', out);
	g_hash_table_destroy (includeNames);
}

void
generate_header_forward_declaration (FILE *out, Structure *structure)
{
	gchar *typeName;
	gchar *typeKind;
	Structure *parentStructure;
	gchar *upperCamel;
	gchar *ownUpperCamel;
	GHashTable *includeNames;
	GHashTableIter iter_table;
	gpointer key;
	gpointer value;
	
	g_return_if_fail (out != NULL && structure != NULL);
	
	includeNames = g_hash_table_new_full (g_str_hash, g_str_equal, NULL, NULL);
	
	/* Temporary solution. To be rewritten */	
	for (g_hash_table_iter_init (&iter_table, structure->dependencies); g_hash_table_iter_next (&iter_table, &key, &value);) {
		typeName = (gchar *)key;
		if (g_hash_table_contains (type2structure, typeName)) {
			parentStructure = g_hash_table_lookup (type2structure, typeName);
			upperCamel = g_strconcat (parentStructure->nameSpace, parentStructure->name, NULL);
			ownUpperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
			if (g_strcmp0 (upperCamel, ownUpperCamel) == 0) {
				g_free (upperCamel);
				g_free (ownUpperCamel);
				continue;
			}

			typeKind = g_hash_table_lookup (type2kind, typeName);
			if (g_strcmp0 (typeKind, "std") == 0) {
				g_hash_table_insert (includeNames, typeName, (gchar *)"std");
			}
			g_free (upperCamel);
			g_free (ownUpperCamel);
		}
	}
	
	typeName = NULL;

	for (g_hash_table_iter_init (&iter_table, includeNames); g_hash_table_iter_next (&iter_table, &key, &value);) {
		typeName = (gchar *)key;
		fwrite ("typedef struct _", sizeof (gchar), strlen ("typedef struct _"), out);
		fwrite (typeName, sizeof (gchar), strlen (typeName), out);
		fputc (' ', out);
		fwrite (typeName, sizeof (gchar), strlen (typeName), out);
		fputc (';', out);
		fputc ('\n', out);
	}
	if (typeName != NULL) {
		fputc ('\n', out);
	}

	g_hash_table_destroy (includeNames);
}

void
generate_source (FILE *out, Structure *structure, GHashTable* table)
{
	FILE *in;
	
	g_return_if_fail (out != NULL && structure != NULL && table != NULL);

	in = open_file (templates_dir, SOURCE_TEMPLATE);
	generate_code_from_template (in, out, structure, table);
	fclose (in);
}

void
generate_source_structure_boilerplate (FILE *out, Structure *structure, GHashTable* table)
{
	FILE *in;
	
	g_return_if_fail (out != NULL && structure != NULL && table != NULL);

	in = open_file (templates_dir, SOURCE_STRUCTURE_BOILERPLATE_TEMPLATE);
	generate_code_from_template (in, out, structure, table);
	fclose (in);
}

GHashTable *
get_hash_table_from_structure (Structure *structure)
{
	GHashTable *table;
	
	gchar *upperCamel;
	gchar *lowerSnake;
	gchar *upperSnake;	
	gchar *lowerTrain;
	gchar *namespaceLowerSnake;
	gchar *nameLowerSnake;
	
	g_return_val_if_fail (structure != NULL, NULL);
	
	table = g_hash_table_new_full (g_str_hash, g_str_equal, NULL, g_free);
	g_hash_table_insert (table, (char *)"commonHeader", g_strdup (COMMON_HEADER));
	upperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
	lowerSnake = get_lower_snake_from_upper_camel (upperCamel);
	upperSnake = get_upper_snake_from_lower_snake (lowerSnake);
	lowerTrain = get_lower_train_from_lower_snake (lowerSnake);
	namespaceLowerSnake = get_upper_snake_from_upper_camel (structure->nameSpace);
	nameLowerSnake = get_upper_snake_from_upper_camel (structure->name);
	
	g_hash_table_insert (table, (char *)"upperCamel", upperCamel);
	g_hash_table_insert (table, (char *)"lowerSnake", lowerSnake);
	g_hash_table_insert (table, (char *)"upperSnake", upperSnake);
	g_hash_table_insert (table, (char *)"lowerTrain", lowerTrain);
	g_hash_table_insert (table, (char *)"namespaceLowerSnake", namespaceLowerSnake);
	g_hash_table_insert (table, (char *)"nameLowerSnake", nameLowerSnake);
	
	if (structure->native != NULL) {
		g_hash_table_insert (table, (char *)"set_owner", get_source_method_proto_set_owner(structure));
		g_hash_table_insert (table, (char *)"set_native", get_source_method_proto_set_native (structure));
		g_hash_table_insert (table, (char *)"set_is_global", get_source_method_proto_set_is_global(structure));
		g_hash_table_insert (table, (char *)"set_property", get_source_method_proto_set_property(structure));
		g_hash_table_insert (table, (char *)"get_property", get_source_method_proto_get_property(structure));
		g_hash_table_insert (table, (char *)"new_full", get_source_method_proto_new_full(structure));
		if (structure->destroyFunc != NULL) {
			g_hash_table_insert (table, (char *)"destroyFunc", g_strdup (structure->destroyFunc));
		} else {
			g_hash_table_insert (table, (char *)"destroyFunc", g_strdup ((gchar *)"g_free"));
		}
		if (structure->cloneFunc != NULL) {
			g_hash_table_insert (table, (gchar *)"cloneFunc", g_strdup (structure->cloneFunc));
		}
		if (structure->isBare) {
			g_hash_table_insert (table, (gchar *)"defaultNative", g_strdup (structure->defaultNative));
		}
	}

	g_hash_table_insert (table, (char *)"native", g_strdup (structure->native));
		
	return table;
}

void 
generate_conditional (FILE *out, Structure *structure, gchar *statement, GHashTable * table)
{
	gint iter;
	gboolean isNegate;
	gboolean isTrue;
	gchar *condition;
	gchar *expression;	
	gchar *buffer;		
	gint count;	
	gint len;
	gchar c;
	gchar *var;	
	gchar *val;
	
	g_return_if_fail (out != NULL && structure != NULL && statement != NULL && *statement != '\0');
	
	iter = 0;
	isNegate = FALSE;
	isTrue = FALSE;
	condition = g_new (gchar, BUFFER_SIZE);
	*condition = '\0';
	expression = g_new (gchar, BUFFER_SIZE);
	*expression = '\0';
	var = g_new (gchar, BUFFER_SIZE);
	*var = '\0';
	count = 0;
	
	if (statement[0] == '!') {
		isNegate = TRUE;
		iter = 1;
	}	
	g_return_if_fail (iter + 1 < strlen (statement) && statement[iter++] == '$' && statement[iter++] == '{');
	while (iter < strlen (statement) && statement[iter] != '}') {
		len = strlen (condition);
		condition[len] = statement[iter++];
		condition[len+1] = '\0';
	}
	
	if (g_strcmp0 (condition, "isBare") == 0) {
		isTrue = structure->isBare;
	} else if (g_strcmp0 (condition, "isPossibleGlobal") == 0) {
		isTrue = structure->isPossibleGlobal;
	} else {
		printf ("The condition variable of %s is not recognized\n", condition);
	}
	g_free (condition);
	
	g_stpcpy (expression, statement+iter+1);
	if ((isNegate && !isTrue) || (!isNegate && isTrue)) {
		for (iter = 0; iter < strlen (expression); iter++) {
			if (iter < strlen(expression)-1 && expression[iter] == '$' && expression[iter+1] == '^') {
				iter += 2;
				count = 1;
				buffer = g_new (gchar, BUFFER_SIZE);
				*buffer = '\0';
				while (iter < strlen (expression)) {
					if (iter < strlen (expression)-1 && expression[iter] == '^' && expression[iter+1] == '$')
						--count;
					if (iter < strlen (expression)-1 && expression[iter] == '$' && expression[iter+1] == '^')
						++count;
					
					if (count == 0) {
						iter += 1;
						generate_conditional (out, structure, buffer, table);
						g_free (buffer);						
						break;
					}
					len = strlen(buffer);
					buffer[len] = expression[iter];
					buffer[len+1] = '\0';
					++iter;
				}
			} else {
				c = expression[iter];
				if (c == '$') {
					if ((c = expression[++iter]) != '{') {
						printf ("The following char is not {");
						return;
					}


					while ((c = expression[++iter]) != '}') {
						len = strlen (var);
						var[len] = c;
						var[len+1] = '\0';
					}

					if (g_hash_table_contains (table, var)) {
						val = g_hash_table_lookup (table, var);
						fwrite (val, sizeof (gchar), strlen (val), out);
						val = NULL;
					} else {
						printf ("The string %s is not recognized in conditional, please check the template\n", var);
						return;
					}
					var[0] = '\0';
				} else {
					fputc (c, out);
				}
			}
		}
	}
	g_free (expression);
	g_free (var);
}

gchar *
get_source_method_code (Method *method)
{
	gchar *buffer;
	gchar *ret;
	GList *iter;
	gchar *para;
	
	buffer = g_new (gchar, BUFFER_SIZE);
	*buffer = '\0';

	g_stpcpy (buffer + strlen (buffer), method->corresponds);
	g_stpcpy (buffer + strlen (buffer), " ");
	
	if (method->parameters == NULL) {
		g_stpcpy (buffer + strlen (buffer), "()");
	} else {
		for (iter = g_list_first (method->parameters); iter != NULL; iter = g_list_next (iter)) {
			if (iter == g_list_first (method->parameters)) {
				g_stpcpy (buffer + strlen (buffer), "(");
			} else {
				g_stpcpy (buffer + strlen (buffer), ", ");
			}
			para = get_inline_parameter ((Parameter *)iter->data);
			g_stpcpy (buffer + strlen (buffer), para);
			g_free (para);
		}
		g_stpcpy (buffer + strlen (buffer), ")");
	}

	ret = g_malloc (strlen (buffer) + 1);
	g_stpcpy (ret, buffer);
	g_free (buffer);
	
	return ret;
}

gchar *
get_translator_for_parameter (Parameter *para)
{
	gchar *trueType;
	gchar *res;
	gchar *structureKind;
	gboolean is_bare;
	Structure *structure;
	
	g_return_val_if_fail (para != NULL, NULL);

	res = NULL;
	is_bare = FALSE;

	if (para->translator != NULL) {
		if (g_strcmp0 (para->translator, (gchar *)"NONE") != 0)
			res = g_strdup (para->translator);
	} else {
		trueType = get_true_type (para->type);
		if (g_hash_table_contains (type2kind, trueType)) {
			structureKind = g_strdup (g_hash_table_lookup (type2kind, trueType));
			structure = g_hash_table_lookup (type2structure, trueType);
			if (structure == NULL) {
				printf ("ERROR: There is no corresponding structure for type %s\n", trueType);
			} else {
				is_bare = structure->isBare;
			}
			if (g_strcmp0 (structureKind, "enum") != 0) {
				/* If the kind of parameter is specified */
				if (para->native_op != NULL) {
					if (g_strcmp0 (para->native_op, "OBJECT") == 0) {
						res = g_strconcat ("* (", structure->native, " *) i_cal_object_get_native", NULL);
					} else if (g_strcmp0 (para->native_op, "POINTER") == 0) {
						res = g_strconcat ("(", structure->native, " *)i_cal_object_get_native", NULL);
					} else if (g_strcmp0 (para->native_op, "STEAL") == 0) {
						res = g_strconcat ("(", structure->native, " *)i_cal_object_steal_native", NULL);
					} else {
						printf ("The parameter kind \"%s\" is illegal!", para->native_op);
						fflush (NULL);
					}
				} else {
					if (is_bare) {
						res = g_strconcat ("* (", structure->native, " *) i_cal_object_get_native", NULL);
					} else {
						res = g_strconcat ("(", structure->native, " *)i_cal_object_get_native", NULL);
					}
				}
			}
			g_free (structureKind);
		}
		g_free (trueType);
	}
	
	return res;
}
gchar *
get_translator_for_return (Ret *ret)
{
	gchar *trueType;
	gchar *lowerSnake;
	gchar *res;
	gchar *kind;
	
	g_return_val_if_fail (ret != NULL, NULL);
	
	res = NULL;

	if (ret->translator != NULL) {
		if (g_strcmp0 (ret->translator, (gchar *)"NONE") != 0)
			res = g_strdup (ret->translator);
	} else {
		trueType = get_true_type (ret->type);
		if (g_hash_table_contains (type2kind, trueType)) {
			kind = g_strdup (g_hash_table_lookup (type2kind, trueType));
			if (g_strcmp0 (kind, "enum") != 0) {
				lowerSnake = get_lower_snake_from_upper_camel (trueType);
				res = g_strconcat (lowerSnake, "_new_full", NULL);
				g_free (lowerSnake);
			}
			g_free (kind);
		}
		g_free (trueType);
	}
	
	return res;
}

gchar *
get_inline_parameter (Parameter *para)
{
	gchar *buffer;
	gchar *ret;
	gchar *translator;
	
	buffer = g_new (gchar, BUFFER_SIZE);
	*buffer = '\0';
	translator = get_translator_for_parameter (para);
	
	if (para->native_op != NULL && translator == NULL) {
		g_error ("No translator is found for parameter %s with type %s but native_op %s is supplied\n", para->name, para->type, para->native_op);
	}

	if (translator != NULL) {
		g_stpcpy (buffer + strlen (buffer), translator);
		g_stpcpy (buffer + strlen (buffer), " (");
		if (para->translator == NULL)
			g_stpcpy (buffer + strlen (buffer), "I_CAL_OBJECT (");
	}

	g_stpcpy (buffer + strlen (buffer), para->name);
	
	if (translator != NULL) {
		if (para->translator == NULL)
			g_stpcpy (buffer + strlen (buffer), ")");
		g_stpcpy (buffer + strlen (buffer), ")");
	}

	/*
	if (translator != NULL)	{
		if (para->translatorArgus != NULL) {
			for (iter = g_list_first (para->translatorArgus); iter != NULL; iter = g_list_next (iter)) {
				g_stpcpy (buffer + strlen (buffer), ", ");
				g_stpcpy (buffer + strlen (buffer), (gchar *)iter->data);
			}
		}

		else if (para->translator == NULL) {
			trueType = get_true_type (para->type);
			if (g_hash_table_contains (type2structure, trueType)) {
				structure = g_hash_table_lookup (type2structure, trueType);
				if (structure->isBare == FALSE) {
					g_stpcpy (buffer + strlen (buffer), ", NULL");				
				}
			}
			g_free (trueType);
		}
		g_stpcpy (buffer + strlen (buffer), ")");
		g_free (translator);
	}
	*/
	ret = g_new (gchar, strlen (buffer) + 1);
	g_stpcpy (ret, buffer);
	g_free (buffer);
	buffer = NULL;
	
	return ret;
}

gchar *
get_source_method_body (Method *method, const gchar *nameSpace)
{
	gchar *buffer;
	gchar *ret;
	gchar *body;
	gchar *proto;
	gchar *comment;
	GList *iter;
	gchar *checkers;
	gchar *translator;
	gchar *trueType;
	Structure *structure;
	Parameter *parameter;
	
	buffer  = g_new (gchar, BUFFER_SIZE);
	buffer[0] = '\0';
	translator = NULL;
	
	comment = get_source_method_comment (method);
	g_stpcpy (buffer + strlen (buffer), comment);
	g_free (comment);
	
	g_stpcpy (buffer + strlen (buffer), "\n");
	
	proto = get_source_method_proto (method);
	g_stpcpy (buffer + strlen (buffer), proto);
	g_free (proto);
	
	g_stpcpy (buffer + strlen (buffer), "\n{\n");
	
	if (g_strcmp0 (method->corresponds, (gchar *)"CUSTOM") != 0) {
		checkers = get_source_run_time_checkers (method, nameSpace);
		if (checkers != NULL) {
			g_stpcpy (buffer + strlen (buffer), checkers);
			g_free (checkers);
		}

		/*op on the owner */
		/* TODO: Change the translatorArgus in Parameter to parent */
		for (iter = g_list_first (method->parameters); iter != NULL; iter = g_list_next (iter)) {
			parameter = (Parameter *)iter->data;
			if (parameter->owner_op != NULL) {
				if (g_strcmp0 (parameter->owner_op, "REMOVE") == 0) {
					g_stpcpy (buffer + strlen (buffer), "\ti_cal_object_remove_owner (I_CAL_OBJECT (");
					g_stpcpy (buffer + strlen (buffer), parameter->name);
					g_stpcpy (buffer + strlen (buffer), "));\n");
				} else {
					g_stpcpy (buffer + strlen (buffer), "\ti_cal_object_set_owner ((ICalObject *)");
					g_stpcpy (buffer + strlen (buffer), parameter->name);
					g_stpcpy (buffer + strlen (buffer), ", (GObject *)");
					g_stpcpy (buffer + strlen (buffer), (gchar *)parameter->owner_op);
					g_stpcpy (buffer + strlen (buffer), ");\n");
				}
			} else if (parameter->translatorArgus != NULL) {
				g_stpcpy (buffer + strlen (buffer), "\ti_cal_object_set_owner ((ICalObject *)");
				g_stpcpy (buffer + strlen (buffer), parameter->name);
				g_stpcpy (buffer + strlen (buffer), ", (GObject *)");
				g_stpcpy (buffer + strlen (buffer), (gchar *)parameter->translatorArgus->data);
				g_stpcpy (buffer + strlen (buffer), ");\n");
			}
		}

		g_stpcpy (buffer + strlen (buffer), "\t");
		if (method->ret != NULL) {
			g_stpcpy (buffer + strlen (buffer), "return ");
			translator = get_translator_for_return (method->ret);
			if (translator != NULL) {
				g_stpcpy (buffer + strlen (buffer), translator);
				g_stpcpy (buffer + strlen (buffer), " (");
			}
		}

		body = get_source_method_code (method);
		g_stpcpy (buffer + strlen (buffer), body);
		g_free (body);

		if (method->ret != NULL && translator != NULL) {
			if (method->ret->translatorArgus != NULL) {
				if (g_strcmp0 ((gchar *) method->ret->translatorArgus->data, "NONE") != 0) {
					for (iter = g_list_first (method->ret->translatorArgus); iter != NULL; iter = g_list_next (iter)) {
						g_stpcpy (buffer + strlen (buffer), ", ");
						g_stpcpy (buffer + strlen (buffer), (gchar *)iter->data);
					}
				}
			} else {
				trueType = get_true_type (method->ret->type);
				if (g_hash_table_contains (type2structure, trueType)) {
					structure = g_hash_table_lookup (type2structure, trueType);
					if (structure->isBare == FALSE) {
						g_stpcpy (buffer + strlen (buffer), ", NULL");
					}
				}
				g_free (trueType);
				/*
				if (g_strcmp0 (g_hash_table_lookup (allTypes, method->ret->type), "true") == 0) {
					g_stpcpy (buffer + strlen (buffer), ", ");
					g_stpcpy (buffer + strlen (buffer), "FALSE");
				}
				 * */
			}
			g_stpcpy (buffer + strlen (buffer), ")");
			g_free (translator);
		}
		g_stpcpy (buffer + strlen (buffer), ";");
	} else if (method->custom != NULL) {
		g_stpcpy (buffer + strlen (buffer), method->custom);
	} else {
		printf ("WARNING: No function body for the method: %s\n", method->name);
	}
	g_stpcpy (buffer + strlen (buffer), "\n}");
	
	ret = g_new (gchar, strlen (buffer) + 1);
	g_stpcpy (ret, buffer);
	g_free (buffer);
	
	return ret;
}

gchar *
get_source_method_proto (Method *method)
{
	gchar *buffer;
	GList *iter_list;
	Parameter *para;
	gchar *ret;
	gint paddingLength;
	gchar *padding;
	gint iter;
	
	buffer = g_new (gchar, BUFFER_SIZE);
	*buffer = '\0';
	
	/* Generate the method return */
	if (method->ret == NULL) {
		g_stpcpy (buffer + strlen (buffer), "void");
	} else {
		g_stpcpy (buffer + strlen (buffer), method->ret->type);
	}
	g_stpcpy (buffer + strlen (buffer), "\n");
	
	/* Generate the method name */
	g_stpcpy (buffer + strlen (buffer), method->name);
	
	paddingLength = strlen (method->name) + 2;
	padding = g_new (gchar, paddingLength+1);
	for (iter = 0; iter < paddingLength; iter++) {
		padding[iter] = ' ';
	}
	padding[iter] = '\0';
	
	/* Generate all the parameters */
	if (method->parameters == NULL) {
		g_stpcpy (buffer + strlen (buffer), " (void)");
	} else {
		for (iter_list = g_list_first (method->parameters); iter_list != NULL; iter_list = g_list_next (iter_list)) {
			para = (Parameter *)iter_list->data;
			if (iter_list == g_list_first (method->parameters)) {
				g_stpcpy (buffer + strlen (buffer), " (");
			} else {
				g_stpcpy (buffer + strlen (buffer), ", \n");
				g_stpcpy (buffer + strlen (buffer), padding);
			}
			g_stpcpy (buffer + strlen (buffer), para->type);
			if (para->type[strlen (para->type)-1] != '*')
				g_stpcpy (buffer + strlen (buffer), " ");
			g_stpcpy (buffer + strlen (buffer), para->name);
		}
		g_stpcpy (buffer + strlen (buffer), ")");
	}
	
	ret = g_malloc (strlen (buffer) + 1);
	g_stpcpy (ret, buffer);
	g_free (buffer);
	g_free (padding);
	
	return ret;
}

gchar *
get_translator_name_for_return (gchar *upperCamel)
{
	gchar *lowerSnake;
	gchar *res;
	
	g_return_val_if_fail (upperCamel != NULL, NULL);
	lowerSnake = get_lower_snake_from_upper_camel (upperCamel);
	res = g_strconcat (lowerSnake, "_new_full", NULL);
	g_free (lowerSnake);
	return res;
}

gchar *
get_true_type (const gchar *type)
{
	int i;
	int start;
	int end;
	gchar *res;	
	const gchar *constPrefix;
	
	g_return_val_if_fail (type != NULL, NULL);
	
	i = 0;
	start = 0;
	end = strlen (type)-1;
	constPrefix = "const";
	
	for (i = 0; i < strlen (constPrefix) && i < strlen (type) && constPrefix[i] == type[i]; i++);
	
	if (i == strlen (constPrefix)) {
		start = i+1;
	} else {
		start = 0;
	}
	
	if (type[strlen (type)-1] == '*') {
		end = strlen (type)-3;
	}
	
	res = g_new (gchar, end - start + 2);
	for (i = start; i <= end; i++) {
		res[i-start] = type[i];
	}
	res[end-start+1] = '\0';
	return res;
}

static void
initialize_default_value_table ()
{
	defaultValues = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);
	g_hash_table_insert (defaultValues, g_strdup ("gboolean"), g_strdup ("FALSE"));
	g_hash_table_insert (defaultValues, g_strdup ("gdouble"), g_strdup ("0"));
	g_hash_table_insert (defaultValues, g_strdup ("gint"), g_strdup ("0"));
	g_hash_table_insert (defaultValues, g_strdup ("gpointer"), g_strdup ("NULL"));
	g_hash_table_insert (defaultValues, g_strdup ("time_t"), g_strdup ("0"));
}
void
generate_header_and_source (Structure *structure, gchar * dir)
{
	gchar *headerName;
	gchar *sourceName;
	gchar *upperCamel;
	gchar *lowerTrain;
	FILE *header;
	FILE *source;
	GHashTable *table;
	
	g_return_if_fail (structure != NULL);
			
	headerName = g_new (gchar, BUFFER_SIZE);
	*headerName = '\0';
	sourceName = g_new (gchar, BUFFER_SIZE);
	*sourceName = '\0';

	upperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
	lowerTrain = get_lower_train_from_upper_camel (upperCamel);
	g_free (upperCamel);

	g_stpcpy (headerName + strlen (headerName), dir);
	g_stpcpy (headerName + strlen (headerName), lowerTrain);
	g_stpcpy (headerName + strlen (headerName), ".h");
	g_stpcpy (sourceName + strlen (sourceName), dir);
	g_stpcpy (sourceName + strlen (sourceName), lowerTrain);
	g_stpcpy (sourceName + strlen (sourceName), ".c");
	
	header = fopen (headerName, "w");
	source = fopen (sourceName, "w");
	
	table = get_hash_table_from_structure (structure);
	generate_header (header, structure, table);
	generate_source (source, structure, table);
	
	fclose (header);
	fclose (source);	
	g_hash_table_destroy (table);
}

void
generate_header_enums (FILE *out, Structure *structure)
{
	GList *iter;
	Enumeration *enumeration;
	
	g_return_if_fail (out != NULL && structure != NULL);
	
	for (iter = g_list_first (structure->enumerations); iter != NULL; iter = g_list_next (iter)) {
		enumeration = (Enumeration *)iter->data;
		
		generate_header_enum (out, enumeration);
		fputc ('\n', out);
	}
	
}

void
generate_header_enum (FILE *out, Enumeration *enumeration)
{
	GList *iter;
	gchar *nativeName;
	int i;	
	gchar *newName;
	gchar *comment;
	gchar *tmp;
	
	g_return_if_fail (out != NULL && enumeration != NULL);
	
	if (enumeration->defaultNative != NULL) {
		g_hash_table_insert (defaultValues, g_strdup (enumeration->name), g_strdup (enumeration->defaultNative));
	} else {
		g_error ("Please supply a default value for enum type %s by default_native\n", enumeration->name);
	}

	/*Generate the comment block*/
	if (enumeration->comment != NULL) {
		comment = g_strdup ("/**");
		tmp = g_strconcat (comment, "\n * ", enumeration->name, ":", NULL);
		g_free (comment);
		comment = tmp;

		tmp = g_strconcat (comment, "\n * ", enumeration->comment, NULL);
		g_free (comment);
		comment = tmp;

		tmp = g_strconcat (comment, "\n */\n", NULL);
		g_free (comment);
		comment = tmp;

		fwrite (comment, sizeof (gchar), strlen (comment), out);
		g_free (comment);
		comment = NULL;
		tmp = NULL;
	}

	/*Generate the declaration*/
	fwrite ("typedef enum {", sizeof (gchar), strlen ("typedef enum {"), out);
	
	for (iter = g_list_first (enumeration->elements); iter != NULL; iter = g_list_next (iter)) {
		nativeName = (gchar *)iter->data;
		if (iter != g_list_first (enumeration->elements)) {
			fputc (',', out);
		}
		if (strlen (ENUM_HEADER) >= strlen (nativeName)) {
			printf ("The enum name %s is longer than the enum header %s\n", nativeName, ENUM_HEADER);
			continue;
		}
		for (i = 0; i < strlen (ENUM_HEADER); i++) {
			if (ENUM_HEADER[i] != nativeName[i]) {
				break;
			}
		}
		if (i != strlen(ENUM_HEADER)) {
			printf ("The enum name %s cannot be processed\n", nativeName);
			continue;
		}
		if (nativeName[i] == '_') {
			newName = g_strconcat ("I_CAL", nativeName+i, NULL);
		} else {
			newName = g_strconcat ("I_CAL_", nativeName+i, NULL);
		}
		
		fputc ('\n', out);
		fputc ('\t', out);
		fwrite (newName, sizeof (gchar), strlen (newName), out);
		fwrite (" = ", sizeof (gchar), strlen (" = "), out);
		fwrite (nativeName, sizeof (gchar), strlen (nativeName), out);
		
		g_free (newName);
	}
		
	fwrite ("\n} ", sizeof (gchar), strlen ("\n} "), out);
	fwrite (enumeration->name, sizeof (gchar), strlen (enumeration->name), out);
	fputc (';', out);
	fputc ('\n', out);
}

gchar *
get_source_run_time_checkers (Method *method, const gchar *namespace)
{
	GList *iter;
	GList *jter;
	Parameter *parameter;
	int i;
	gchar *buffer;
	gchar *nameSpaceUpperSnake;
	gchar *nameUpperSnake;
	gchar *typeCheck;
	gchar *trueType;
	gchar *res;
	gchar *defaultValue;
	gchar *retTrueType;
	
	g_return_val_if_fail (method != NULL, NULL);
	g_return_val_if_fail (namespace == NULL || *namespace != '\0', NULL);
	
	buffer = g_new (gchar, BUFFER_SIZE);
	*buffer = '\0';
	res = NULL;
	
	for (iter = g_list_first (method->parameters); iter != NULL; iter = g_list_next (iter)) {
		parameter = (Parameter *)iter->data;
		
		if (namespace != NULL && parameter->type[strlen (parameter->type)-1] == '*') {
			trueType = get_true_type (parameter->type);
			for (i = 0; i < strlen (namespace) && i < strlen (parameter->type) && namespace[i] == trueType[i]; i++);
			
			if (i == strlen (namespace)) {
				g_stpcpy (buffer + strlen (buffer), "\t");
				nameSpaceUpperSnake = get_upper_snake_from_upper_camel (namespace);
				nameUpperSnake = get_upper_snake_from_upper_camel (trueType+i);
				typeCheck = g_strconcat (nameSpaceUpperSnake, "_IS_", nameUpperSnake, " (", parameter->name, ")", NULL);
				defaultValue = NULL;
				if (method->ret != NULL) {
					retTrueType = get_true_type (method->ret->type);
					g_stpcpy (buffer + strlen (buffer), "g_return_val_if_fail (");
					g_stpcpy (buffer + strlen (buffer), typeCheck);
					g_stpcpy (buffer + strlen (buffer), ", ");
					if (method->ret->errorReturnValue != NULL) {
						defaultValue = g_strdup (method->ret->errorReturnValue);
					} else if (method->ret->type[strlen (method->ret->type)-1] == '*') {
						defaultValue = g_strdup ("NULL");
					} else if (g_hash_table_contains (defaultValues, retTrueType)) {
						defaultValue = g_strdup (g_hash_table_lookup (defaultValues, retTrueType));
					} else {
						printf ("No default value provided for the return type %s in method %s\n", method->ret->type, method->name);
						defaultValue = g_strdup ("NULL");
					}
					g_free(retTrueType);
					g_stpcpy (buffer + strlen (buffer), defaultValue);
					g_free (defaultValue);
					g_stpcpy (buffer + strlen (buffer), ");");
				} else {
					g_stpcpy (buffer + strlen (buffer), "g_return_if_fail (");
					g_stpcpy (buffer + strlen (buffer), typeCheck);
					g_stpcpy (buffer + strlen (buffer), ");");
				}
				g_free (nameSpaceUpperSnake);
				g_free (nameUpperSnake);
				g_free (typeCheck);
				g_stpcpy (buffer + strlen (buffer), "\n");
			}
			
			for (jter = g_list_first (parameter->annotations); jter != NULL; jter = g_list_next (jter)) {
				if (g_strcmp0 ((gchar *)jter->data, "allow-none") == 0) {
					break;
				}
			}
			
			if (jter == NULL) {
				g_stpcpy (buffer + strlen (buffer), "\t");
				if (method->ret != NULL) {
					g_stpcpy (buffer + strlen (buffer), "g_return_val_if_fail (");
					g_stpcpy (buffer + strlen (buffer), parameter->name);
					g_stpcpy (buffer + strlen (buffer), " != NULL, ");
					defaultValue = NULL;
					if (method->ret->errorReturnValue != NULL) {
						defaultValue = g_strdup (method->ret->errorReturnValue);
					} else if (method->ret->type[strlen (method->ret->type)-1] == '*') {
						defaultValue = g_strdup ("NULL");
					} else if (g_hash_table_contains (defaultValues, (retTrueType = get_true_type (method->ret->type)))) {
						defaultValue = g_strdup (g_hash_table_lookup (defaultValues, retTrueType));
						g_free(retTrueType);
					} else {
						printf ("No default value provided for the return type %s in method %s\n", method->ret->type, method->name);
						defaultValue = g_strdup ("NULL");
					}
					g_stpcpy (buffer + strlen (buffer), defaultValue);
					g_free (defaultValue);
					g_stpcpy (buffer + strlen (buffer), ");");
				} else {
					g_stpcpy (buffer + strlen (buffer), "g_return_if_fail (");
					g_stpcpy (buffer + strlen (buffer), parameter->name);
					g_stpcpy (buffer + strlen (buffer), " != NULL");
					g_stpcpy (buffer + strlen (buffer), ");");
				}
				g_stpcpy (buffer + strlen (buffer), "\n");
			}
			g_free (trueType);
		}
	}
	
	if (strlen (buffer) > 0) {
		res = g_strconcat (buffer, "\n", NULL);
	}
	g_free (buffer);
	return res;
}

static gint generate_library (gint count, char **fileNames) {
	xmlDoc *doc;
	xmlNode *node;
	Structure *structure;
	gchar *path;
	Enumeration *enumeration;
	gchar *buffer;
	GList *structures;
	GList *iter_list;
	gint iter_general;
	
	g_return_val_if_fail (count >= 0, 1);
	
	buffer = g_new (gchar, BUFFER_SIZE);
	*buffer = '\0';

	/* Cache the type and its kind, like ICalComponnet--->std or ICalPropertyKind--->enum */
	type2kind = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);
	/* Cache the type and the structure where it is defined, like ICalComponent--->Structure_storing_ICalComponent */
	type2structure = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);

	initialize_default_value_table ();
	structures = NULL;

	/* Parse the all the XML files into the Structure */
	for (iter_general = 0; iter_general < count; iter_general++){
		path = g_build_filename (apis_dir, fileNames[iter_general], NULL);
		doc = xmlParseFile (path);
		if (doc == NULL) {
			printf ("The doc %s cannot be parsed.\n", path);
			return 1;
		}
		g_free (path);

		node = xmlDocGetRootElement (doc);
		if (node == NULL) {
			printf ("The root node cannot be retrieved from the doc\n");
			return 1;
		}

		structure = structure_new ();
		if (!parse_structure (node, structure)) {
			printf ("The node cannot be parsed into a structure.\n");
			return 1;
		}
		
		if (structure->native != NULL) {
			g_hash_table_insert (type2kind, g_strconcat (structure->nameSpace, structure->name, NULL), (void *)"std");
			g_hash_table_insert (type2structure, g_strconcat (structure->nameSpace, structure->name, NULL), structure);
			if (structure->isBare) {
				if (structure->defaultNative != NULL) {
					g_hash_table_insert (defaultValues, g_strconcat (structure->nameSpace, structure->name, NULL), g_strdup (structure->defaultNative));
				} else {
					printf ("Please supply a default value for the bare structure %s\n", structure->name);
					return 1;
				}
			}
		}
		
		for (iter_list = g_list_first (structure->enumerations); iter_list != NULL; iter_list = g_list_next (iter_list)) {
			enumeration = (Enumeration *)iter_list->data;
			g_hash_table_insert (type2kind, g_strdup (enumeration->name), (void *)"enum");
			g_hash_table_insert (type2structure, g_strdup (enumeration->name), structure);

			if (enumeration->defaultNative != NULL) {
				g_hash_table_insert (defaultValues, g_strdup (enumeration->name), g_strdup (enumeration->defaultNative));
			} else {
				printf ("Please supply a default value for enum %s\n", enumeration->name);
				return 1;
			}
		}
		structures = g_list_append (structures, structure);
		xmlFreeDoc (doc);
	}

	/* Generate the common header for all the headers, which is libical-glib.h for here */
	generate_header_header_file (structures);

	/* Generate all the header and source files for each structure */
	for (iter_list = g_list_first (structures); iter_list != NULL; iter_list = g_list_next (iter_list)) {
		structure = (Structure *)iter_list->data;
		generate_header_and_source (structure, (char*)"");
	}
	
	g_hash_table_destroy (type2kind);
	g_hash_table_destroy (type2structure);
	g_hash_table_destroy (defaultValues);
	for (iter_list = g_list_first (structures); iter_list != NULL; iter_list = g_list_next (iter_list)) {
		structure = (Structure *)iter_list->data;
		structure_free (structure);
	}
	g_list_free (structures);
	g_free (buffer);

	return 0;
}

void
generate_header_header_declaration (FILE *out, Structure *structure)
{
	GList *list_iter;
	Declaration *declaration;

	g_return_if_fail (out != NULL && structure != NULL);

	for (list_iter = g_list_first (structure->declarations); list_iter != NULL; list_iter = g_list_next (list_iter)) {
		declaration = (Declaration *)list_iter->data;

		if (g_strcmp0 (declaration->position, "header") == 0) {
			fwrite (declaration->content, sizeof (gchar), strlen (declaration->content), out);
			fputc ('\n', out);
		}
		declaration = NULL;
	}
}

void
generate_header_header_file (GList *structures)
{
	FILE *out;
	FILE *in;
	gchar c;
	gchar *buffer;
	GList *iter;
	gint len;
	gchar *header;
	gchar *upperCamel;
	gchar *lowerTrain;
	Structure *structure;

	g_return_if_fail (structures != NULL);

	in = open_file (templates_dir, HEADER_HEADER_TEMPLATE);
	out = fopen ("libical-glib.h", "w");

	buffer = g_new (gchar, BUFFER_SIZE);
	*buffer = '\0';

	while ((c = fgetc (in)) != EOF) {
		if (c == '$') {
			if ((c = fgetc (in)) != '{' && c != '^') {
				printf ("The following char is not {");
				return;
			}


			while ((c = fgetc (in)) != '}') {
				len = strlen (buffer);
				buffer[len] = c;
				buffer[len+1] = '\0';
			}

			if (g_strcmp0 (buffer, "allHeaders") == 0) {
				for (iter = g_list_first (structures); iter != NULL; iter = g_list_next (iter)) {
					structure = (Structure *)iter->data;
					upperCamel = g_strconcat (structure->nameSpace, structure->name, NULL);
					lowerTrain = get_lower_train_from_upper_camel (upperCamel);
					header = g_strconcat ("#include <libical-glib/", lowerTrain, ".h>\n", NULL);
					fwrite (header, sizeof (gchar), strlen (header), out);
					g_free (header);
					g_free (upperCamel);
					g_free (lowerTrain);
					structure = NULL;
				}
			} else {
				printf ("The string %s is not recognized, please check the header-header-template\n", buffer);
				fflush (NULL);
				return;
			}
			buffer[0] = '\0';
		} else {
			fputc (c, out);
		}
	}

	g_free (buffer);
}

int
main (int argc,
      char *argv[])
{
	gchar **fileNames;
	gint iter_general;
	gint res;
	
	if (argc < 4) {
		fprintf (stderr, "Requires two arguments, the first is path to templates, the second an XML file name with an API description\n");
		return 1;
	}

	/* The directory to search for templates */
	templates_dir = argv[1];
	/* The directory to search for XML files */
	apis_dir = argv[2];

	fileNames = g_new (gchar *, argc-3);
	for (iter_general = 3; iter_general < argc; iter_general++) {
		fileNames[iter_general-3] = argv[iter_general];
	}
	
	res = generate_library (argc-3, fileNames);
	
	for (iter_general = 0; iter_general < argc-3; iter_general++) {
		fileNames[iter_general] = NULL;
	}
	g_free (fileNames);

	return res;
}
