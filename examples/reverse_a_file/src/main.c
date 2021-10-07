#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

uint8_t reverseFileContents(char *pSrc, char *pDest)
{
    uint8_t status = 1;
    FILE *pSrcFile, *pDestFile;

    Stack_t s;
    char buf[1000];
    Stack_Init(&s, buf, sizeof(buf), sizeof(buf[0]));

    pSrcFile = fopen(pSrc, "r");
    pDestFile = fopen(pDest, "w");

    if (pSrcFile == NULL || pDestFile == NULL)
    {
        status = 0;
    }

    if (status == 1)
    {
        char fileChar;
        do
        {
            fileChar = fgetc(pSrcFile);
            Stack_Push(&s, &fileChar);
        } while (!feof(pSrcFile));

        while (!Stack_IsEmpty(&s))
        {
            Stack_Pop(&s, &fileChar);
            fputc(fileChar, pDestFile);
        }

        fclose(pSrcFile);
        fclose(pDestFile);
    }

    return status;
}

int main(int argc, char *argv[])
{
    uint8_t status = reverseFileContents("/home/banderson/Desktop/stack/examples/reverse_a_file/src/input_text.txt",
                                     "/home/banderson/Desktop/stack/examples/reverse_a_file/src/output_text.txt");
    if (status == 1)
    {
        printf("File copied successfully!\n");
    }
    else
    {
        printf("Error: copy failed!\n");
    }

    return 0;
}