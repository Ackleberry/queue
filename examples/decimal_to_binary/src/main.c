#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void printBinary(uint64_t inputValue)
{
    const uint8_t base = 2;
    const uint8_t groupBitsBy = 4;

    Stack_t s;
    bool buf[64];
    Stack_Init(&s, buf, sizeof(buf), sizeof(buf[0]));

    printf("Binary value of %lld: ", inputValue);

    if (inputValue == 0)
    {
        printf("0");
    }
    while (inputValue > 0)
    {
        int rem = inputValue % base;
        Stack_Push(&s, &rem);

        inputValue /= base;
    }

    for (uint8_t zeros = groupBitsBy - (s.top % groupBitsBy); zeros > 1; zeros--)
    {
        printf("0");
    }

    size_t elements = s.top + 1;
    while (!Stack_IsEmpty(&s))
    {
        uint8_t bit;
        Stack_Pop(&s, &bit);
        printf("%d", bit);
        elements--;

        if (elements % groupBitsBy == 0)
        {
            printf(" ");
        }
    }

    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        char *string;
        int value = strtol(argv[1], &string, 10);
        printBinary(value);
    }
    else
    {
        printf("Error: Invalid number of arguments.\n");
    }

    return 0;
}