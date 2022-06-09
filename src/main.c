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

#define LENGTH 300

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

    char text_txt[LENGTH]= "This is, a - test";
    char buf[LENGTH];
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
    
    printf("Length: %lu\n", strlen(buf));

    printf("Round 2, split a long text in parts with a certain length.\n");
    memset(buf, 0, LENGTH);
    char oldbuf[10][300];
    char whole_text[10][300];
    int line_counter=0;

    strcpy (text_txt, "This is, a - test with a much longer text. It has more letters, more spaces, more of everything. But still is totally meaningless. ");
    pch = strtok (text_txt, " ,.-");    // Split text. 
    strcpy(buf,pch);                    // Store first part.
    strcpy(whole_text[line_counter], buf);  // Save first item
    strcat(whole_text[line_counter], " ");
    strcpy(oldbuf[line_counter], buf);      // Save old buffer

    while (pch != NULL)
    {
        pch = strtok (NULL, " ,-");
        if(pch != NULL) 
        {
            char *T = pch;
            strcat(buf,T);                         // Add next word  
            strcat(whole_text[line_counter], T);
            strcat(whole_text[line_counter], " ");

            if (strlen(whole_text[line_counter]) >= 15)   // Oops, got to long, go to next line.
            {
                printf ("%s - %lu\n", whole_text[line_counter], strlen(whole_text[line_counter]));
                strcpy(whole_text[line_counter],oldbuf[line_counter]);  // Get back previous line
                line_counter++;
            }
            strcat(buf,T);
            strcat(oldbuf[line_counter], T);
        }
        if(pch == NULL)
        {
            printf ("%s - %lu\n", whole_text[line_counter], strlen(whole_text[line_counter]));   // The last word
        }
    }
    return 0;
}