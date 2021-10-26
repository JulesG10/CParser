#include <stdio.h>
#include "css_parser.h"

int main(int argc, char **argv)
{
    string test;
    strconvert(".aze, .b , .a { backgroundColor:red, url(\"nice\") ; }", &test);

    int index = 0;
    css_style style;

    if (parse_id(&index, test, &style))
    {
        printf("EXIT_SUCCESS");
        return EXIT_SUCCESS;
    }
    else
    {
        printf("EXIT_FAILURE");
        return EXIT_FAILURE;
    }
}