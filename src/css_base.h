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

typedef struct css_attr_v css_attr_v;

typedef enum css_type
{
    NUMBER,
    STR,
    FUNCTION,
    ATTR_PARAM,
    INNER_CONTEXT,
    NONE
} css_attr_type;

typedef struct css_num_v
{
    string num_type;
    string num_value;
} css_num_v;
typedef struct css_func
{
    size_t length;
    css_attr_v *values;
    string func_name;
} css_func;

typedef struct css_innerctx
{
    size_t length;
    css_attr_v *values;
} css_innerctx;

struct css_attr_v
{
    css_num_v num;
    css_func func;
    css_innerctx ctx;
    string data;

    css_attr_type type;
};


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