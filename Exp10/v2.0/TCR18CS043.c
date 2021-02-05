#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Creating a structure to hold optab and symtab

typedef struct _optab{
    char name[25];
    char code[25];
}optab;

// This function is used to convert a string number to 
// an actual integer.

int convertStringToInt(char number[25])
{
    int result = 0;
    int i = 0;

    for(i = 0; number[i] != '\0'; i++)
    {
        result = result * 10 + (number[i] - '0');
    }

    return result;
}

// This function is used to convert an actual integer to 
// a string integer.

void convertIntToString(char number[25], int intNumber)
{
    char tempNumber[25] = "";
    int it = 0;
    int n;

    while(intNumber != 0)
    {
        tempNumber[it] = '0' + intNumber % 10;
        intNumber /= 10;
        it++;
    }

    n = it;

    for(it = 0; it < n; it++)
    {
        number[it] = tempNumber[n -it - 1];
    }

    number[n] = '\0';
}

// This is used to add leading zeros to a string.

void stringPadderLeft(char string[25], int reqLength, char padChar[2])
{
    int i;
    char reqString[25] = "";

    for(i = 0; i < (reqLength - (int)strlen(string)); i++)
    {
        strcat(reqString, padChar);

    }

    strcat(reqString, string);
    reqString[reqLength] = '\0';

    strcpy(string, reqString);
}

// This is used to add trailing spaces to a string.

void stringPadderRight(char string[25], int reqLength, char padChar[2])
{
    int i;
    char reqString[25] = "";

        strcpy(reqString, string);

    for(i = (int)strlen(string) - 1; i < reqLength; i++)
    {
        strcat(reqString, padChar);

    }

    reqString[reqLength] = '\0';

    strcpy(string, reqString);
}

// This function is to convert a decimal number to a hexadecimal
// string.

void decimalToHexadecimal(char hexNumber[25], int n) 
{         
    int temp;
    int i = 0; 

    char hexaDeciNum[25] = "";
    strcpy(hexNumber, "0");

    while(n!=0) 
    {    
        temp  = 0; 
        
        // storing remainder in temp variable. 
        temp = n % 16; 
          
        // check if temp < 10 
        if(temp < 10) 
        { 
            hexaDeciNum[i] = temp + 48; 
            i++; 
        } 
        else
        { 
            hexaDeciNum[i] = temp + 87; 
            i++; 
        } 
          
        n = n/16; 
    } 
    
    for(int j = 0; j < i; j++) 
        hexNumber[j] = hexaDeciNum[i - j - 1];
} 


// Implementation of one pass assembler

void onePassAssembler()
{
    printf("\n\t\t-----ONE-PASS ASSEMBLER------\n");
    FILE * filePointerIn = NULL;
    FILE * filePointerInOpTab = NULL;
    FILE * filePointerOutSymTab = NULL;
    FILE * filePointerOutOutput = NULL;
    FILE * filePointerOutResult = NULL;
    char fileName[25], opTabName[25], symTabName[25];
    char programLengthString[25];
    char one[25] = "", two[25] = "", three[25] = "";
    int memoryStart = 0, memoryLocation = 0;
    int number;

    char headerRecord[23] = "H";
    char textRecord[200] = "T";
    char addressUpdate[25][50];
    char endRecord[9] = "E";
    char output[25][50];

    int it, operationTableSize;
    int addressIt = 0, addressUpdateSize;

    optab operationTable[25];

    printf("Enter the input file name: ");
    scanf("%s", fileName);

    printf("Enter OPTAB name: ");
    scanf("%s", opTabName);

    filePointerIn = fopen(fileName, "r");
    filePointerInOpTab = fopen(opTabName, "r");
    filePointerOutSymTab = fopen("symtab.txt", "w");
    filePointerOutOutput = fopen("output.txt", "w");
    filePointerOutResult = fopen("result.txt", "w");

    // Checking if input and output files are accessible.

    if(filePointerIn == NULL || filePointerInOpTab == NULL || filePointerOutSymTab == NULL || filePointerOutOutput == NULL || filePointerOutResult == NULL)
    {
        printf("I/O failed. Terminating.\n");
        exit(0);
    }

    // Reading OPTAB

    it = 0;

    while(fscanf(filePointerInOpTab, "%s %s", one, two) != EOF)
    {
        strcpy(operationTable[it].name, one);

        stringPadderLeft(two, 2, "0");
            
        strcpy(operationTable[it].code, two);
    
        ++it;   
    }

    operationTableSize = it;

    while(strcmp(two, "END") != 0)
    {
        // Read the three arguements

        fscanf(filePointerIn, "%s %s %s", one, two, three);

        // If it is START statement

        if(strcmp(two, "START") == 0)
        {
            // Get Starting memory location.

            memoryStart = convertStringToInt(three);
            memoryLocation = memoryStart;
        }
        else
        {
            it = 0;

            while(it < operationTableSize)
            {
                // Find out if operand and output to symtab

                if(strcmp(two, operationTable[it].name) == 0)
                {
                    fprintf(filePointerOutSymTab, "%s\t*\n", three);
                }

                ++it;
            }


            // If RESW define the variable in symtab
            // If a Word is reserverd then memory location has to be updated accordingly

            if(strcmp(two, "RESW") == 0)
            {
                fprintf(filePointerOutSymTab, "%s\t%d\n",one, memoryLocation);
            
                convertIntToString(programLengthString, memoryLocation);
                strcpy(operationTable[it].code, programLengthString);
                strcpy(operationTable[it].name, one);
                operationTableSize++;

                number = convertStringToInt(three);
                memoryLocation += number * 3;
            }
            else if(strcmp(two, "END") != 0)
            {
                // Otherwise just add 3.

                memoryLocation += 3;
            }
        }
        

    }

    fclose(filePointerIn);
    filePointerIn = fopen(fileName, "r");

    strcpy(two, "");

    // Loop until END is reached

    while(strcmp(two, "END") != 0)
    {
        // Read the three arguements
        

        fscanf(filePointerIn, "%s %s %s", one, two, three);

        // If it is START statement

        if(strcmp(two, "START") == 0)
        {
            // Get Starting memory location.

            memoryStart = convertStringToInt(three);
            memoryLocation = memoryStart;
            
            // Add to header record.
            
            strcat(headerRecord, "^");

            stringPadderRight(one, 6, " ");
            strcat(headerRecord, one);
        

            strcat(headerRecord, "^");

            stringPadderLeft(three, 6, "0");
            strcat(headerRecord, three);

            strcat(headerRecord, "^");

            // Add to end record.

            strcat(endRecord, "^");
            strcat(endRecord, three);

            // Add to text record.

            strcat(textRecord, "^");
            strcat(textRecord, three);

            strcat(textRecord,"^  ");
        }        
        else
        {       
            it = 0;

            while(it < operationTableSize)
            {
                // Find out which opertation is performed and
                // add the necessary opcode.

                if(strcmp(two, operationTable[it].name) == 0)
                {
                    strcat(textRecord, "^");
                    strcat(textRecord, operationTable[it].code);

                    fprintf(filePointerOutOutput, "%s\t0\n", operationTable[it].code);

                    while(it < operationTableSize)
                    {
                        // Find out which data is used and
                        // add the necessary address.
                        if(strcmp(three, operationTable[it].name) == 0)
                        {   
                            strcpy(addressUpdate[addressIt], "T^");
                            convertIntToString(programLengthString, memoryLocation + 1);
                            strcat(addressUpdate[addressIt], programLengthString);
                            strcat(addressUpdate[addressIt],"^02^");                      
                            strcat(addressUpdate[addressIt], operationTable[it].code);
                            
                            strcpy(output[addressIt], programLengthString);
                            strcat(output[addressIt], "\t");
                            strcat(output[addressIt], operationTable[it].code);

                            ++addressIt;

                            strcat(textRecord, "0000");
                        }
                        ++it;   
                    }
                }

                ++it;
            }

            // If a constant is used, add the constant to the text record.

            if(strcmp(two, "WORD") == 0)
            {
                stringPadderLeft(three, 6, "0");

                strcat(textRecord, "^");
                strcat(textRecord, three);
            }

            // If a Word is reserverd then memory location has to be updated accordingly

            if(strcmp(two, "RESW") == 0)
            {
                number = convertStringToInt(three);
                memoryLocation += number * 3;
            }
            else if(strcmp(two, "END") != 0)
            {
                // Otherwise just add 3.

                memoryLocation += 3;
            }
        }        
    }

    addressUpdateSize = addressIt;

    // Calculate the program length.
    decimalToHexadecimal(programLengthString, memoryLocation - memoryStart);

    // Add length to header record.

    stringPadderLeft(programLengthString, 6, "0");
    strcat(headerRecord, programLengthString);

    // Add length to text record

    textRecord[9] = programLengthString[4];
    textRecord[10] = programLengthString[5];

    fprintf(filePointerOutResult, "%s\n", headerRecord);
    fprintf(filePointerOutResult, "%s\n", textRecord);

    for(it = 0; it < addressUpdateSize; it++)
    {
        fprintf(filePointerOutResult, "%s\n", addressUpdate[it]);

        fprintf(filePointerOutOutput, "%s\n", output[it]);
    }

    fprintf(filePointerOutResult, "%s\n", endRecord);

    printf("\nOutput generated");
    printf("\n[info] output -> output.txt");
    printf("\n[info] Symbol table -> symtab.txt");
    printf("\n[info] Object program -> result.txt\n");

    fclose(filePointerIn);
    fclose(filePointerInOpTab);
    fclose(filePointerOutSymTab);
    fclose(filePointerOutOutput);
    fclose(filePointerOutResult);    
}

int main()
{
    onePassAssembler();
    return 0;
}