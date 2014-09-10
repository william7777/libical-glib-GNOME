/* 
 * File:   xml-parser.h
 * Author: williamyu
 *
 * Created on June 23, 2014, 8:24 PM
 */

#ifndef XML_PARSER_H
#define	XML_PARSER_H

#include <libxml2/libxml/xmlreader.h>
#include <stdio.h>
#include <glib-2.0/glib.h>

typedef struct Parameter {
	gchar *type;
	GList *annotations;
	gchar *comment;
	gchar *name;
        gchar *autofill;
        gchar *translator;
        GList *translatorArgus;
} Parameter;

typedef struct Ret {
	gchar *type;
	GList *annotations;
	gchar *comment;
        gchar *translator;
        GList *translatorArgus;
        gchar *errorReturnValue;
        gchar *cloner;
        GList *clonerArgus;
} Ret;

typedef struct Method {
	gchar *name;
	gchar *corresponds;
	gchar *kind;
	gchar *since;
	GList *parameters;
	Ret *ret;
	gchar *comment;
	gchar *custom;
	GList *annotations;
} Method;

typedef struct Structure {
        gchar *nameSpace;
	gchar *name;
	gchar *native;
	GList *includes;
	GList *methods;
        gchar *parent;
        gchar *parentType;
        gboolean isBare;
        gboolean isPossibleGlobal;
        GList *enumerations;
        GHashTable *dependencies;
        gchar *destroyFunc;
        gchar *cloneFunc;
        gchar *defaultNative;
} Structure;

typedef struct Enumeration {
        gchar *name;
        GList *elements;
} Enumeration;

Structure *structure_new ();
void structure_free(Structure *structure);
Method *method_new ();
void method_free (Method *method);
Parameter *parameter_new ();
void parameter_free (Parameter *para);
Ret *ret_new ();
void ret_free (Ret *ret);
Enumeration *enumeration_new ();
void enumeration_free (Enumeration *enumeration);

GList *get_list_from_string (const gchar *str);
gchar *get_true_type (const gchar *type);
void populate_dependencies (Structure *structure);
gboolean parse_parameters (xmlNode *node, Method *method);
gboolean parse_return (xmlNode *node, Method *method);
gboolean parse_comment (xmlNode *node, Method *method);
gboolean parse_method (xmlNode *node, Method *method);
gboolean parse_structure (xmlNode *node, Structure *structure);
gboolean parse_enumeration (xmlNode *node, Enumeration *enumeration);
gboolean parse_custom(xmlNode *node, Method *method);

#endif	/* XML_PARSER_H */

