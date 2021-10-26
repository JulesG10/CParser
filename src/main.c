#include <stdio.h>
#include "css_parser.h"

int main(int argc, char **argv)
{
    for (size_t i = 1; i < argc; i++)
    {
        FILE *file = fopen(argv[i], "r");
        if (file)
        {
            printf("File %s\n", argv[i]);

            string fileContent;
            strbuild(&fileContent, "", 0);

            char line[255];

            while (fgets(line, 255, file))
            {
                for (int j = 0; j < strlen(line); j++)
                {
                    stradd(&fileContent, line[j]);
                }
            }
            fclose(file);

            if (fileContent.length > 0)
            {
                int index = 0;
                while (index < fileContent.length)
                {
                    printf("\n");

                    css_style style;
                    if (!parse_id(&index, fileContent, &style))
                    {
                        return EXIT_FAILURE;
                    }

                    remove_none(&index, fileContent);
                }
            }else{
                printf("File is empty\n");
            }
        }
    }

    // string text;
    // strconvert(".aze, .b , .a { backgroundColor:red, url(\"nice\", hello, 12px), \"test_string\" ; test-aze:none; }", &text);

    return EXIT_SUCCESS;
}