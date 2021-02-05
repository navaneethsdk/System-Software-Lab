#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// This function is to initialize strings to blank values.

void initializeString(char str[10][25], int size)
{
    int i;

    for(i = 0; i < size; i++)
    {
        strcpy(str[i], "");
    }
}

// Implementation of two pass macro assembler.

void twoPassMacroAssembler()
{
    FILE * filePointerIn = NULL;
    FILE * filePointerOutDTab = NULL;
    FILE * filePointerOutNTab = NULL;
    FILE * filePointerOutATab = NULL;
    FILE * filePointerOutOutput = NULL;

    FILE * filePointerInDtab = NULL;

    char fileName[50];

    char one[25] = "", two[25] = "", three[25] = "";

    char macroNames[10][25];
    int macroNamesIt = 0, macroNamesSize;
    int insertNeeded = 0;

    char formalArguements[10][25];
    char actualArguements[10][25];
    char tempString[2];
    int arguementIt = 0, numberOfArguements;

    int i;
    initializeString(macroNames, 10);
    initializeString(formalArguements, 10);
    initializeString(actualArguements, 10);

    printf("Enter file name: ");
    scanf("%s", fileName);

    filePointerIn = fopen(fileName, "r");
    filePointerOutDTab = fopen("dtab.txt", "w");
    filePointerOutNTab = fopen("ntab.txt", "w");
    filePointerOutATab = fopen("atab.txt", "w");
    filePointerOutOutput = fopen("output.txt", "w");

    if(filePointerIn == NULL || filePointerOutDTab == NULL || filePointerOutNTab == NULL || filePointerOutATab == NULL || filePointerOutOutput == NULL)
    {
        printf("I/O failed. Terminating.\n");
        return;
    }

    // Pass one, look for macros, loop until macro end MEND.
    
    while(strcmp(two, "MEND") != 0)
    {
        fscanf(filePointerIn, "%s %s %s", one, two, three);
        
        if(strcmp(two, "MACRO") == 0)
        {

            // If MACRO, output name to ntab and dtab.

            fprintf(filePointerOutNTab, "%s\n", one);
            fprintf(filePointerOutDTab, "%s\t%s\n", one, three);

            strcpy(macroNames[macroNamesIt], one);
            ++macroNamesIt;

            // Get formal arguements and store to an array.

            for(i = 0; three[i] != '\0'; i++)
            {
                if(three[i] == ',')
                {
                    ++arguementIt;
                    ++i;
                }

                tempString[0] = three[i];
                tempString[1] = '\0';
                strcat(formalArguements[arguementIt], tempString);
            }
        }
        else if(strcmp(two, "MEND") == 0)
        {
            fprintf(filePointerOutDTab, "%s\n", two);
        }
        else
        {
            
            // Output macro body to dtab.

            fprintf(filePointerOutDTab, "%s\t%s\n", two, three);
        }
    }

    macroNamesSize = macroNamesIt;
    numberOfArguements = arguementIt + 1;
    arguementIt = 0;

    fclose(filePointerOutDTab);

    printf("Pass one complete, dtab and ntab available.\n");

    filePointerInDtab = fopen("dtab.txt", "r");

    if(filePointerInDtab == NULL)
    {
        printf("I/O failed. Terminating.\n");
        return;   
    } 
    
    // Begin pass two, reset file input.

    fseek(filePointerIn, 0, SEEK_SET);
    strcpy(two, "");

    // Loop until END is reached.

    while(strcmp(two, "END") != 0)
    {
        fscanf(filePointerIn, "%s %s %s", one, two, three);
        
        // If MACRO body is reached, don't write to output

        if(strcmp(two, "MACRO") == 0)
        {
            while(strcmp(two, "MEND") != 0)
            {
                fscanf(filePointerIn, "%s %s %s", one, two, three);
            }
            
            fscanf(filePointerIn, "%s %s %s", one, two, three);
        }

        // Check if a macro is called.
        
        for(i = 0; i < macroNamesSize; i++)
        {

            // If yes, get actual arguements.

            if(strcmp(two, macroNames[i]) == 0)
            {
                for(i = 0; three[i] != '\0'; i++)
                {
                    if(three[i] == ',')
                    {
                        ++arguementIt;
                        ++i;
                    }

                    tempString[0] = three[i];
                    tempString[1] = '\0';
                    strcat(actualArguements[arguementIt], tempString);
                }

                // Print actual arguements to atab

                for(i = 0; i < numberOfArguements; i++)
                {
                    fprintf(filePointerOutATab, "%s\n", actualArguements[i]);
                }

                // Set to insert MACRO body.

                insertNeeded = 1;
                break;
            }
        }
        
        // Insert MACRO body.

        if(insertNeeded == 1)
        {
            fprintf(filePointerOutOutput, "%s\t%s\t%s\n", one, two, three);
            fscanf(filePointerInDtab, "%s\t%s", one, two);

            // Insert MACRO until MEND

            while(1)
            {            
                fscanf(filePointerInDtab, "%s", one);

                if(strcmp(one, "MEND") == 0)
                {
                    fscanf(filePointerIn, "%s %s %s", one, two, three);
                    break;
                }

                fscanf(filePointerInDtab, "%s", two);

                // Replace formal arguements with actual arguements.

                for(i = 0; i < numberOfArguements; i++)
                {
                    if(strcmp(two, formalArguements[i]) == 0)
                    {
                        strcpy(two, actualArguements[i]);
                    }
                }

                fprintf(filePointerOutOutput, "-\t%s\t%s\n", one, two);
            }

            insertNeeded = 0;
        }

        fprintf(filePointerOutOutput, "%s\t%s\t%s\n", one, two, three);
        
    }

    printf("Pass two complete, atab and output available.\n");

    fclose(filePointerIn);
    fclose(filePointerOutNTab);
    fclose(filePointerOutATab);
    fclose(filePointerOutOutput);
    fclose(filePointerInDtab);
}

int main()
{
    twoPassMacroAssembler();
    
    return 0;
}