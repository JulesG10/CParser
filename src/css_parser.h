#ifndef _PARSER_
#define _PARSER_

#include <stdlib.h>
#include <stdbool.h>

#include "./str.h"
#include "./css_base.h"
#include "./parser_util.h"

bool parse_func_type(int *index, string text, css_func *func);
enum css_type getnext_type(int *index, string text);
bool parse_attrname_type(int *index, string text, string *out);
bool parse_number_type(int *index, string text, css_num_v *num);
bool parse_string_type(int *index, string text, string *out);
bool parse_attr_value(int *index, string text, css_attr_v **values, size_t *values_length);
bool parse_css_attr(int *index, string text, css_attr *attr);
bool parse_style_ctx(int *index, string text, css_style *style);
bool parse_id(int *index, string text, css_style *style);

enum css_type getnext_type(int *index, string text)
{
    string numvalid;
    strbuild(&numvalid, "0123456789", 10);
    if (strstart(text.buffer[(*index)], numvalid))
    {
        return NUMBER;
    }

    if (text.buffer[(*index)] == STRING)
    {
        return STR;
    }

    if (text.buffer[(*index)] == CTX_START)
    {
        return INNER_CONTEXT;
    }

    int tmpI = (*index);
    if (strstart(text.buffer[tmpI], VALID_NAME))
    {
        string tmpName;
        strbuild(&tmpName, "", 0);
        get_namevalid(&tmpI, text, &tmpName, VALID_NAME);
        if (tmpName.length != 0)
        {
            if (text.buffer[tmpI] == PARAM_START)
            {
                return FUNCTION;
            }
        }

        return ATTR_PARAM;
    }

    return NONE;
}

bool parse_func_type(int *index, string text, css_func *func)
{
    remove_none(index, text);
    strbuild(&func->func_name, "", 0);

    get_namevalid(index, text, &func->func_name, VALID_NAME);
    if (func->func_name.length == 0)
    {
        printf("invalid function name\n");
        return false;
    }

    func->length = 0;
    func->values = malloc(sizeof(css_attr_v) * func->length);

    if (expect_c(index, text, PARAM_START))
    {
        for (int i = (*index); i < text.length; i++)
        {
            remove_none(&i, text);
            enum css_type type = getnext_type(&i, text);

            if (type == NONE)
            {
                i++;
                remove_none(&i, text);
                if (expect_c(&i, text, PARAM_END))
                {
                    (*index) = i;
                    return true;
                }
                break;
            }
            else if (type == STR)
            {
                func->length++;
                func->values = realloc(func->values, sizeof(css_attr_v) * func->length);
                func->values[func->length].type = type;

                strbuild(&func->values[func->length].data, "", 0);

                if (!parse_string_type(&i, text, &func->values[func->length].data))
                {
                    return false;
                }

                remove_none(&i, text);
                if (text.buffer[i] == PARAM_END)
                {
                    i++;
                    (*index) = i;
                    return true;
                }
                else if (text.buffer[i] == NEXT_VALUE)
                {
                    i++;
                }
                else
                {
                    return false;
                }
            }
            else if (type == NUMBER)
            {
                func->length++;
                func->values = realloc(func->values, sizeof(css_attr_v) * func->length);
                func->values[func->length].type = type;

                strbuild(&func->values[func->length].num.num_value, "", 0);
                strbuild(&func->values[func->length].num.num_type, "", 0);

                if (!parse_number_type(&i, text, &func->values[func->length].num))
                {
                    return false;
                }

                remove_none(&i, text);
                if (text.buffer[i] == PARAM_END)
                {
                    i++;
                    (*index) = i;
                    return true;
                }
                else if (text.buffer[i] == NEXT_VALUE)
                {
                    i++;
                }
                else
                {
                    return false;
                }
            }
            else if (type == ATTR_PARAM)
            {
                func->length++;
                func->values = realloc(func->values, sizeof(css_attr_v) * func->length);
                func->values[func->length].type = type;
                if (!parse_attrname_type(&i, text, &func->values->data))
                {
                    return false;
                }

                remove_none(&i, text);
                if (text.buffer[i] == PARAM_END)
                {
                    i++;
                    (*index) = i;
                    return true;
                }
                else if (text.buffer[i] == NEXT_VALUE)
                {
                    i++;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}

bool parse_attrname_type(int *index, string text, string *out)
{
    get_namevalid(index, text, out, VALID_NAME);
    if (out->length == 0)
    {
        return false;
    }

    return true;
}

bool parse_number_type(int *index, string text, css_num_v *num)
{
    string numvalid;
    strbuild(&numvalid, "0123456789", 10);

    if (!strstart(text.buffer[(*index)], numvalid))
    {
        return false;
    }

    get_namevalid(index, text, &num->num_value, VALID_NUMBER);
    if (num->num_value.length == 0)
    {
        return false;
    }

    get_namevalid(index, text, &num->num_type, VALID_NAME);
    if (num->num_type.length == 0)
    {
        return false;
    }

    return true;
}

bool parse_string_type(int *index, string text, string *out)
{
    if (expect_c(index, text, STRING))
    {
        int i = (*index);
        for (i = i; i < text.length; i++)
        {
            if (text.buffer[i] == STRING)
            {
                i++;
                (*index) = i;
                return true;
            }
            stradd(out, text.buffer[i]);
        }
    }

    return false;
}

bool parse_attr_value(int *index, string text, css_attr_v **values, size_t *values_length)
{
    size_t sizeV = (*values_length);

    for (int i = (*index); i < text.length; i++)
    {
        remove_none(&i, text);
        if (text.buffer[i] == END_ATTRIBUTE)
        {
            // i++;
            (*index) = i;
            break;
        }
        else
        {
            enum css_type type = getnext_type(&i, text);
            sizeV++;
            (*values) = realloc((*values), sizeof(css_attr_v) * sizeV);

            if (type == FUNCTION)
            {
                if (!parse_func_type(&i, text, &(*values)[sizeV - 1].func))
                {
                    printf("invalid function type %c\n", text.buffer[i]);
                    return false;
                }
            }
            else if (type == STR)
            {
                strbuild(&(*values)[sizeV - 1].data, "", 0);
                if (!parse_string_type(&i, text, &(*values)[sizeV - 1].data))
                {
                    printf("invalid string type %c\n", text.buffer[i]);
                    return false;
                }
            }
            else if (type == NUMBER)
            {
                strbuild(&(*values)[sizeV - 1].num.num_type, "", 0);
                strbuild(&(*values)[sizeV - 1].num.num_value, "", 0);

                if (!parse_number_type(&i, text, &(*values)[sizeV - 1].num))
                {
                    printf("invalid number type %c\n", text.buffer[i]);
                    return false;
                }
            }
            else if (type == INNER_CONTEXT)
            {
                printf("(TODO) inner_context %c\n", text.buffer[i]);
                return false;
            }
            else if (type == ATTR_PARAM)
            {
                strbuild(&(*values)[sizeV - 1].data, "", 0);
                if (!parse_attrname_type(&i, text, &(*values)[sizeV - 1].data))
                {
                    printf("invalid attr value %c\n", text.buffer[i]);
                    return false;
                }
            }
            else
            {
                printf("no type found %c\n", text.buffer[i]);
                return false;
            }

            remove_none(&i, text);
            if (text.buffer[i] == END_ATTRIBUTE)
            {
                // i++;
                (*index) = i;
                break;
            }
            else if (text.buffer[i] == NEXT_VALUE)
            {
                i++;
            }
            else
            {
                printf("invalid next attribute value %c\n", text.buffer[i]);
                return false;
            }
        }
    }

    return true;
}

bool parse_css_attr(int *index, string text, css_attr *attr)
{
    attr->name.length = 0;
    attr->name.buffer = malloc(sizeof(char) * 0);

    attr->values_length = 0;
    attr->values = malloc(sizeof(css_attr_v) * attr->values_length);

    int i = (*index);
    remove_none(&i, text);
    get_namevalid(&i, text, &attr->name, VALID_PARTS_NAME);

    if (attr->name.length > 0)
    {
        if (expect_c(&i, text, START_ATTRIBUTE))
        {
            printf("attribute <");
            strprint(attr->name);
            printf(">\n");

            remove_none(&i, text);

            if (!parse_attr_value(&i, text, &attr->values, &attr->values_length))
            {
                printf("invalid attribute value\n");
                return false;
            }
            
            remove_none(&i, text);

            if (!expect_c(&i, text, END_ATTRIBUTE))
            {
                printf("invalid end attr\n");
                return false;
            }
        }
        else
        {
            printf("invalid start attr\n");
            return false;
        }
    }
    (*index) = i;
     return true;
}

bool parse_style_ctx(int *index, string text, css_style *style)
{
    style->attr_length = 0;
    style->attributes = malloc(sizeof(css_attr) * 0);

    remove_none(index, text);
    for (int i = (*index); i < text.length; i++)
    {
        remove_none(index, text);
        if (text.buffer[i] == CTX_END)
        {
            (*index) = i;
            break;
        }
        else
        {
            style->attr_length++;
            style->attributes = realloc(style->attributes, sizeof(css_attr) * style->attr_length);

            if (!parse_css_attr(&i, text, &(style->attributes[style->attr_length - 1])))
            {
                return false;
            }
            remove_none(&i,text);
            if (text.buffer[i] == CTX_END)
            {
                (*index) = i;
                break;
            }
        }
    }

    return true;
}

bool parse_id(int *index, string text, css_style *style)
{
    remove_none(index, text);

    style->id_length = 0;
    style->id_list = (string *)malloc(sizeof(string) * style->id_length);

    for (int i = (*index); i < text.length; i++)
    {
        remove_none(&i, text);
        if (expect_c(&i, text, ID_START))
        {
            style->id_length++;
            style->id_list = (string *)realloc(style->id_list, style->id_length * sizeof(string));
            size_t last = style->id_length - 1;

            style->id_list[last].length = 0;
            style->id_list[last].buffer = malloc(sizeof(char) * 0);

            get_namevalid(&i, text, &(style->id_list[last]), VALID_ID);

            if (style->id_list[last].length > 0)
            {
                printf("id <");
                strprint(style->id_list[last]);
                printf(";%d>\n", style->id_list[last].length);

                remove_none(&i, text);
                if (text.buffer[i] != NEXT_VALUE)
                {
                    if (expect_c(&i, text, CTX_START))
                    {
                        printf("start <context>\n");
                        if (!parse_style_ctx(&i, text, style))
                        {
                            return false;
                        }

                        if (text.buffer[i] != CTX_END)
                        {
                            printf("invalid ctx end %c\n", text.buffer[i]);
                            return false;
                        }

                        printf("end <context>\n");
                        break;
                    }
                    else
                    {
                        printf("invalid next %c\n", text.buffer[i]);
                        return false;
                    }
                }
            }
        }
        else
        {

            printf("invalid next %c\n", text.buffer[i]);
            return false;
        }
    }

    return true;
}
#endif // !_PARSER_