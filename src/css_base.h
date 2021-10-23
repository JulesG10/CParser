#ifndef _CSS_
#define _CSS_

#include <stdlib.h>
#include "str.h"

#define NEW_LINE '\n'
#define SPACE ' '
#define END_ATTRIBUTE ';'
#define START_ATTRIBUTE ':'
#define CTX_START '{'
#define CTX_END '}'
#define ID_START '.'
#define STRING '\"'
#define PARAM_START '('
#define PARAM_END ')'
#define NEXT_VALUE ','

typedef enum css_attr_type
{
    PERCENT,
    FLOAT,
    STR,
    FUNCTION,
    ATTRIBUTE_PARAM,
    INNER_CONTEXT
} css_attr_type;

typedef struct css_attr_v
{
    css_attr_type value_type;
    string value_data;
} css_attr_v;

typedef struct css_attr
{
    string name;
    css_attr_v *values;
    size_t values_length;
} css_attr;

typedef struct css_style
{
    string *id_list;
    size_t id_length;

    css_attr *attributes;
    size_t attr_length;
} css_style;

#endif // !_CSS_