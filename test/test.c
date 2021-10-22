#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/str.h"

void showbits( unsigned char x )
{
    for (int i = (sizeof(char) * 8) - 1; i >= 0; i--)
    {
       printf("%c",x & (1u << i) ? '1' : '0');
    }
   
}

void print_str(char *str, size_t len)
{
    for (int i = 0; i < len; i++)
    {
        printf("[%d] %d %c\n", i, (int)str[i], str[i]);
    }
    printf("\n");
}

void set_data(char **buff)
{
    size_t len = 2;

    *buff = (char *)realloc(*buff, sizeof(char) * len);
    *buff = (char *)memset(*buff, (int)'a', len);
    free(*buff);

    *buff = (char *)malloc(sizeof(char) * len);
    *buff = (char *)memset(*buff, (int)'a', len);
    print_str(*buff, len);

    char *tmp = (char *)malloc(len * sizeof(char));
    tmp = (char *)memset(tmp, (int)'b', len);
    print_str(tmp, len);

    tmp = (char *)memmove(tmp, *buff, len * sizeof(char));
    print_str(tmp, len);

    tmp[0] = 'c';
    print_str(tmp, len);

    printf("tmp == buff %s\n", memcmp(tmp, *buff, len) ? "false" : "true");

    free(tmp);
}

int main(int argc, char **argv)
{
    // char* buffer = NULL;
    // set_data(&buffer);
    // print_str(buffer,2);
    // free(buffer);

    string test;
    strbuild(&test, "1-4", 5);

    string *list = malloc(sizeof(string));
    size_t len = strsplit(&test, '-', &list);

    for (size_t i = 0; i < len; i++)
    {
        strdebug(list[i]);
    }

    strfill(&test, 'a');
    strdebug(test);

    strjoin(list, len, '-', &test);
    strdebug(test);

    strnadd(&test,"-2-3",1);
    strdebug(test);

    string tmp;
    strfree(&tmp);

    strcopy(&tmp, &test);
    strdebug(tmp);

    printf("%s\n",test.buffer);
    printf("%d %d\n", strlen(test.buffer), sizeof(test.buffer));

    for (size_t i = 0; i < test.length; i++)
    {
        printf("%c\t%d\t", test.buffer[i], (int)test.buffer[i]);
        showbits((unsigned char)test.buffer[i]);
        // printf("\t ~");
        // showbits((unsigned char)~test.buffer[i]);

        printf("\n");
    }
    

    return 0;
}