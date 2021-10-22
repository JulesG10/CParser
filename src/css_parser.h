#ifndef _PARSER_
#define _PARSER_

#include <stdlib.h>
#include <stdbool.h>

#include "./str.h"
#include "./css_base.h"
#include "./parser_util.h"

// void strfix(string *t)
// {
//     if (strlen(t->buffer) != t->length)
//     {
//         char *buff = malloc(t->length * sizeof(char));
//         for (size_t i = 0; i < t->length; i++)
//         {
//             buff[i] = t->buffer[i];
//         }

//         free(t->buffer);
//         t->buffer = malloc(t->length * sizeof(char));
//         t->buffer = strcpy(t->buffer, buff);
//     }
// }

bool parse_attr_value(int *index, string text, css_attr_v *value)
{
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
    get_namevalid(&i, text, &attr->name);

    if (attr->name.length > 0)
    {
        if (expect_c(&i, text, START_ATTRIBUTE))
        {
            remove_none(&i, text);

            css_attr_v value;
            parse_attr_value(&i, text, &value);

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

            get_namevalid(&i, text, &(style->id_list[last]));

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