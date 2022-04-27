/**
 * @file main.c
 * @author Patrik Hermansson (hermansson.patrik@gmail.com)
 * @brief Demo of strncpy, strcpy and strtok.
 * @version 0.1
 * @date 2022-04-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <lib.h>

int main() 
{
    // A function call to show how functions can be placed in external source files. 
    libfunction();

    char filename[128];
    char* name = "hello";
    char* extension = ".txt";

    if (sizeof(filename) < strlen(name) + 1 ) { /* +1 is for null character */
        fprintf(stderr, "Name '%s' is too long\n", name);
        return EXIT_FAILURE;
    }
    strncpy(filename, name, sizeof(filename));

    if (sizeof(filename) < (strlen(filename) + strlen(extension) + 1) ) {
        fprintf(stderr, "Final size of filename is too long!\n");
        return EXIT_FAILURE;
    }
    strncat(filename, extension, (sizeof(filename) - strlen(filename)) );
    printf("Filename is %s\n", filename);

    
    char text_txt[]= "This is, a - test";
    char buf[300];
    printf ("Splitting string \"%s\" into tokens:\n",text_txt);
    
    char *pch; 
    pch = strtok (text_txt, " ,.-");
    strcpy(buf,pch);
    printf ("First part: %s\nOther parts:\n",buf);

    while (pch != NULL)
    {
        pch = strtok (NULL, " ,.-");
        if(pch != NULL) 
        {
            printf ("%s\n",pch);
            char *T = pch;
            strcat(buf,T);
        }
    }
    printf ("All the bits: %s\n",buf);
    
    return 0;
}