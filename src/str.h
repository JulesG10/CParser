#ifndef _STR_
#define _STR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string
{
    char *buffer;
    size_t length;
} string;

void strbuild(string *str, char *text, size_t len);
void stradd(string *str, const char ch);
void strnadd(string *str, char *data, size_t n);
void strpop(string *str);
void strfill(string *str, const char ch);
void strjoin(string *list, size_t list_len, const char ch, string *str);
void strdebug(string str);
void strcopy(string *dst, const string *src);
void strfree(string *str);
void strconvert(char *str, string *dst);
void strprint(string str);
bool strstart(char fistch, string listch);
bool strin(char ch, string str);
size_t strsplit(string *str, const char ch, string **list);

void stradd(string *str, const char ch)
{
    str->length++;
    str->buffer = (char *)realloc(str->buffer, str->length);
    str->buffer[str->length - 1] = ch;
}

void strnadd(string *str, char *data, size_t n)
{
    size_t data_len = strlen(data);
    str->length += data_len;
    str->buffer = (char *)realloc(str->buffer, str->length * sizeof(char));

    string tmp;
    tmp.length = 0;
    tmp.buffer = (char *)malloc(sizeof(char) * 0);

    for (size_t i = n; i < (str->length - data_len); i++)
    {
        stradd(&tmp, str->buffer[i]);
    }

    for (size_t i = n; i < (n + data_len); i++)
    {
        str->buffer[i] = data[i - n];
    }

    for (size_t i = (n + data_len); i < str->length; i++)
    {
        str->buffer[i] = tmp.buffer[i - (n + data_len)];
    }
}

void strpop(string *str)
{
    str->length--;
    str->buffer = (char *)realloc(str->buffer, str->length);
}

void strfill(string *str, const char ch)
{
    memset(str->buffer, (int)ch, str->length);
}

size_t strsplit(string *str, const char ch, string **list)
{
    free(*list);

    size_t index = 0;

    *list = (string *)malloc(sizeof(string) * 1);
    (*list)[index].length = 0;
    (*list)[index].buffer = (char *)malloc(sizeof(char) * 0);

    for (size_t i = 0; i < str->length; i++)
    {
        if (str->buffer[i] != ch)
        {
            stradd(&(*list)[index], str->buffer[i]);
        }
        else
        {
            index++;

            *list = (string *)realloc(*list, sizeof(string) * (index + 1));
            (*list)[index].length = 0;
            (*list)[index].buffer = (char *)malloc(sizeof(char) * 0);
        }
    }

    return index + 1;
}

void strjoin(string *list, size_t list_len, const char ch, string *str)
{
    free(str->buffer);
    str->length = 0;
    str->buffer = malloc(sizeof(char) * 0);

    for (size_t i = 0; i < list_len; i++)
    {
        for (size_t k = 0; k < list[i].length; k++)
        {
            stradd(str, list[i].buffer[k]);
        }

        if (i + 1 != list_len)
        {
            stradd(str, ch);
        }
    }
}

void strdebug(string str)
{
    for (size_t i = 0; i < str.length; i++)
    {
        printf("%c", str.buffer[i]);
    }

    printf(" (%d)\n", str.length);
}

void strbuild(string *str, char *text, size_t len)
{
    str->length = len;
    str->buffer = (char *)malloc(sizeof(char) * str->length);
    str->buffer = strcpy(str->buffer, text);
}

void strfree(string *str)
{
    str->length = 0;
    free(str->buffer);
    str->buffer = (char *)malloc(sizeof(char) * 0);
}

void strcopy(string *dst, const string *src)
{
    dst->length = src->length;
    dst->buffer = memcpy(dst->buffer, src->buffer, src->length);
}

void strconvert(char *str, string *dst)
{
    dst->length = strlen(str) + 1;
    dst->buffer = malloc(sizeof(char) * dst->length);
    dst->buffer = strcpy(dst->buffer, str);
}

void strprint(string str)
{
    for (size_t i = 0; i < str.length; i++)
    {
        printf("%c", str.buffer[i]);
    }
}

bool strin(char ch, string str)
{
    for (size_t k = 0; k < str.length; k++)
    {
        if (ch == str.buffer[k])
        {
            return true;
        }
    }
    return false;
}

bool strstart(char fistch, string listch)
{
    for (int k = 0; k < listch.length; k++)
    {
        if (listch.buffer[k] == fistch)
        {
            return true;
        }
    }
    return false;
}

#endif // !_STR_