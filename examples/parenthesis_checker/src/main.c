#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

bool isLeftDelimiter(char c)
{
    return (c == '(' || c == '{' || c == '[') ? true : false;
}

bool isRightDelimiter(char c)
{
    return (c == ')' || c == '}' || c == ']') ? true : false;
}

bool doDelimitersMatch(char left, char right)
{
    bool ret = false;

    if ((left == '(' && right == ')') ||
        (left == '{' && right == '}') ||
        (left == '[' && right == ']'))
    {
        ret = true;
    }

    return ret;
}

int8_t checkParenthesis(char *pFileName)
{
    uint8_t status = 1;

    FILE *pSrcFile = fopen(pFileName, "r");

    Stack_t s;
    char buf[100];
    Stack_Init(&s, buf, sizeof(buf), sizeof(buf[0]));

    if (pSrcFile == NULL)
    {
        status = 0;
    }

    if (status == 1)
    {
        char fileChar;
        char lastBracket;

        do
        {
            fileChar = fgetc(pSrcFile);

            if (isLeftDelimiter(fileChar))
            {
                Stack_Push(&s, &fileChar);
            }

            if (isRightDelimiter(fileChar))
            {
                if (Stack_Pop(&s, &lastBracket) == Stack_Error)
                {
                    printf("Stack cannot pop.\n");
                    status = 0;
                    break;
                }

                if (doDelimitersMatch(lastBracket, fileChar) == false)
                {
                    printf("Delimiters Don't match.\n");
                    status = 0;
                    break;
                }
            }

        } while (!feof(pSrcFile));

        if (!Stack_IsEmpty(&s))
        {
            printf("Stack is not empty.\n");
            status = 0;
        }

        fclose(pSrcFile);
    }

    return status;
}

int main(int argc, char *argv[])
{
    char *pFileName = "/home/banderson/Desktop/stack/examples/parenthesis_checker/src/input_text.txt";
    uint8_t status = checkParenthesis(pFileName);

    if (status == 1)
    {
        printf("Parenthesis match!\n");
    }
    else
    {
        printf("Error: Parenthesis mismatch!\n");
    }
    return 0;
}