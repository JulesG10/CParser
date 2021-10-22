#ifndef _UTIL_
#define _UTIL_

#include <stdlib.h>
#include <stdbool.h>

#include "./str.h"
#include "./css_base.h"

void getutil(int *index, string text, string *out, char stop);
void remove_none(int *index, string text);
bool expect_c(int *index, string text, char expected);
void get_namevalid(int *index, string text, string *name);

void getutil(int *index, string text, string *out, char stop)
{
    strfree(out);

    for (int i = (*index); i < text.length; i++)
    {
        if (text.buffer[i] == stop)
        {
            (*index) = i;
            break;
        }
        stradd(out, text.buffer[i]);
    }
}

void remove_none(int *index, string text)
{
    for (int i = (*index); i < text.length; i++)
    {
        if (text.buffer[i] != SPACE && text.buffer[i] != NEW_LINE)
        {
            (*index) = i;
            break;
        }
    }
}

bool expect_c(int *index, string text, char expected)
{
    if (text.buffer[(*index)] == expected)
    {
        (*index)++;
        return true;
    }
    return false;
}

void get_namevalid(int *index, string text, string *name)
{
    string valid;
    strconvert("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890", &valid);
    strfree(name);

    for (int i = (*index); i < text.length; i++)
    {
        if (strin(text.buffer[i], valid))
        {
            stradd(name, text.buffer[i]);
        }
        else
        {
            (*index) = i;
            break;
        }
    }
}

#endif // !_UTIL_
