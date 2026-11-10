#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

/* Conversion status codes */
#define CONVERSION_SUCCESS  1
#define INVALID_CHARACTER   0
#define INVALID_DIGIT      -1
#define INTEGER_OVERFLOW   -2
#define NULL_POINTER_ERROR -3
#define INVALID_BASE       -4

/* Function prototypes */
int cleanInputLine(void);
int isValidBase(long base);

int baseToDecimal(const char *num, int base, long long *result);
int decimalToBase(long long decimal, int destinationBase);

/* Clears remaining input and detects unexpected characters. */
int cleanInputLine(void)
{
    int ch;
    int valid = 1;

    while ((ch = getchar()) != '\n')
    {
        if (ch == EOF)
        {
            return -1;
        }

        if (!isspace((unsigned char)ch))
        {
            valid = 0;
        }
    }

    return valid;
}

/* Checks whether a base is supported. */
int isValidBase(long base)
{
    return (base == 2 || base == 8 ||
            base == 10 || base == 16);
}

/* Converts a number from a supported base to decimal. */
int baseToDecimal(const char *num, int base, long long *result)
{
    long long decimal = 0;
    int digit;

    if (num == NULL || result == NULL)
    {
        return NULL_POINTER_ERROR;
    }

    if (!isValidBase(base))
    {
        return INVALID_BASE;
    }

    if (num[0] == '\0')
    {
        return INVALID_CHARACTER;
    }

    for (int i = 0; num[i] != '\0'; i++)
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            digit = num[i] - '0';
        }
        else if (num[i] >= 'A' && num[i] <= 'F')
        {
            digit = num[i] - 'A' + 10;
        }
        else if (num[i] >= 'a' && num[i] <= 'f')
        {
            digit = num[i] - 'a' + 10;
        }
        else
        {
            return INVALID_CHARACTER;
        }

        if (digit >= base)
        {
            return INVALID_DIGIT;
        }

        if (decimal > (LLONG_MAX - digit) / base)
        {
            return INTEGER_OVERFLOW;
        }

        decimal = decimal * base + digit;
    }

    *result = decimal;

    return CONVERSION_SUCCESS;
}

/* Converts a non-negative decimal number to a supported base. */
int decimalToBase(long long decimal, int destinationBase)
{
    int remain;
    char output[65];
    int i = 0;

    if (!isValidBase(destinationBase))
    {
        return INVALID_BASE;
    }

    if (decimal < 0)
    {
        return INVALID_CHARACTER;
    }

    if (decimal == 0)
    {
        printf("0");
        return CONVERSION_SUCCESS;
    }

    while (decimal > 0)
    {
        remain = decimal % destinationBase;

        if (remain < 10)
        {
            output[i] = '0' + remain;
        }
        else
        {
            output[i] = 'A' + (remain - 10);
        }

        decimal /= destinationBase;
        i++;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        printf("%c", output[j]);
    }

    return CONVERSION_SUCCESS;
}

/* Reads and validates a string from standard input. */
int readInput(char *buffer, int size)
{
    int scanStatus;
    int lineStatus;

    scanStatus = scanf("%31s", buffer);

    if (scanStatus == EOF)
    {
        return -1;
    }

    if (scanStatus != 1)
    {
        return 0;
    }

    lineStatus = cleanInputLine();

    if (lineStatus == -1)
    {
        return -1;
    }

    if (lineStatus == 0)
    {
        return 0;
    }

    return 1;
}

/* Safely parses a base supplied as text. */
int parseBase(const char *input, int *base)
{
    char *endptr;
    long parsed;

    errno = 0;

    parsed = strtol(input, &endptr, 10);

    if (errno == ERANGE ||
        endptr == input ||
        *endptr != '\0')
    {
        return 0;
    }

    if (!isValidBase(parsed))
    {
        return 0;
    }

    *base = (int)parsed;

    return 1;
}

int main(void)
{
    char num[32];
    char baseInput[32];
    char destinationInput[32];

    int base;
    int destinationBase;

    long long result;

    int status;

    printf("====================================\n");
    printf("       NUMBER SYSTEM CONVERTER\n");
    printf("====================================\n");

    /* Read number */
    printf("\nEnter number: ");

    status = readInput(num, sizeof(num));

    if (status == -1)
    {
        printf("Unexpected end of input.\n");
        return 1;
    }

    if (status != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    if (num[0] == '-')
    {
        printf("Negative numbers are not supported.\n");
        return 1;
    }

    /* Read source base */
    printf("Enter source base (2, 8, 10, 16): ");

    status = readInput(baseInput, sizeof(baseInput));

    if (status == -1)
    {
        printf("Unexpected end of input.\n");
        return 1;
    }

    if (status != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    if (!parseBase(baseInput, &base))
    {
        printf("Invalid source base.\n");
        return 1;
    }

    /* Convert source number to decimal */
    status = baseToDecimal(num, base, &result);

    if (status != CONVERSION_SUCCESS)
    {
        switch (status)
        {
            case INVALID_CHARACTER:
                printf("Invalid character in number.\n");
                break;

            case INVALID_DIGIT:
                printf("Digit is invalid for the given base.\n");
                break;

            case INTEGER_OVERFLOW:
                printf("Integer overflow detected.\n");
                break;

            case NULL_POINTER_ERROR:
                printf("Null pointer error.\n");
                break;

            case INVALID_BASE:
                printf("Unsupported source base.\n");
                break;

            default:
                printf("Unknown conversion error.\n");
        }

        return 1;
    }

    /* Read destination base */
    printf("Enter destination base (2, 8, 10, 16): ");

    status = readInput(destinationInput, sizeof(destinationInput));

    if (status == -1)
    {
        printf("Unexpected end of input.\n");
        return 1;
    }

    if (status != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    if (!parseBase(destinationInput, &destinationBase))
    {
        printf("Invalid destination base.\n");
        return 1;
    }

    /* Display conversion result */
    printf("\n====================================\n");
    printf("             RESULT\n");
    printf("====================================\n");

    printf("Original number : %s\n", num);
    printf("Source base     : %d\n", base);
    printf("Decimal value   : %lld\n", result);

    printf("Converted value : ");

    status = decimalToBase(result, destinationBase);

    if (status != CONVERSION_SUCCESS)
    {
        printf("\nConversion failed.\n");
        return 1;
    }

    printf("\nDestination base: %d\n", destinationBase);

    printf("====================================\n");

    return 0;
}
