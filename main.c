#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

#define CONVERSION_SUCCESS 1
#define INVALID_CHARACTER 0
#define INVALID_DIGIT -1
#define INTEGER_OVERFLOW -2
#define NULL_POINTER_ERROR -3

// Clears the remaining input line and checks for unexpected characters.
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

// Converts a number from any supported base to decimal.
int baseToDecimal(char num[], int base, long long *result)
{
    long long decimal = 0;
    int digit;

    if (result == NULL)
    {
        return NULL_POINTER_ERROR;
    }

    for (int i = 0; num[i] != '\0'; i++)
    {
        // Identify the digit.
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

        // Validate digit against the source base.
        if (digit >= base)
        {
            return INVALID_DIGIT;
        }

        // Check integer overflow.
        if (decimal > (LLONG_MAX - digit) / base)
        {
            return INTEGER_OVERFLOW;
        }

        // Convert the current digit.
        decimal = decimal * base + digit;
    }

    // Store the final result in the caller's variable.
    *result = decimal;

    return CONVERSION_SUCCESS;
}

// Converts a decimal number to any supported destination base.
void decimalToBase(long long decimal, int destinationBase)
{
    int remain;
    char output[65];
    int i = 0;

    if (decimal == 0)
    {
        printf("0\n");
        return;
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

        decimal = decimal / destinationBase;
        i++;
    }

    // Print the stored digits in reverse order.
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%c", output[j]);
    }

    printf("\n");
}

// Checks whether a base is supported.
int isValidBase(long base)
{
    return (base == 2 || base == 8 || base == 10 || base == 16);
}

int main(void)
{
    char num[32];
    char baseInput[32];
    char destinationInput[32];

    int base;
    int destinationBase;

    long long result;

    long parsedBase;
    long parsedDestination;

    char *endptr;

    int status;
    int scanStatus;

    int conversionStatus;

    // Read the number.
    printf("Enter number: ");

    scanStatus = scanf("%31s", num);

    if (scanStatus == EOF)
    {
        printf("Unexpected end of input.\n");
        return 0;
    }

    if (scanStatus != 1)
    {
        cleanInputLine();
        printf("Invalid input.\n");
        return 0;
    }

    status = cleanInputLine();

    if (status == -1)
    {
        printf("Unexpected end of input.\n");
        return 0;
    }

    if (status == 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    // Reject negative numbers.
    if (num[0] == '-')
    {
        printf("Negative numbers are not supported.\n");
        return 0;
    }

    // Read the source base.
    printf("Enter base: ");

    scanStatus = scanf("%31s", baseInput);

    if (scanStatus == EOF)
    {
        printf("Unexpected end of input.\n");
        return 0;
    }

    if (scanStatus != 1)
    {
        cleanInputLine();
        printf("Invalid input.\n");
        return 0;
    }

    status = cleanInputLine();

    if (status == -1)
    {
        printf("Unexpected end of input.\n");
        return 0;
    }

    if (status == 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    // Parse the source base safely.
    errno = 0;
    parsedBase = strtol(baseInput, &endptr, 10);

    if (errno == ERANGE || endptr == baseInput || *endptr != '\0')
    {
        printf("Invalid base input.\n");
        return 0;
    }

    if (!isValidBase(parsedBase))
    {
        printf("Invalid base. Please enter 2, 8, 10, or 16.\n");
        return 0;
    }

    base = (int)parsedBase;

    // Convert the source number to decimal.
    conversionStatus = baseToDecimal(num, base, &result);

    if (conversionStatus == INVALID_CHARACTER)
    {
        printf("Invalid character.\n");
        return 0;
    }
    else if (conversionStatus == INVALID_DIGIT)
    {
        printf("Invalid digit for the given base.\n");
        return 0;
    }
    else if (conversionStatus == INTEGER_OVERFLOW)
    {
        printf("Integer overflow detected.\n");
        return 0;
    }
    else if (conversionStatus == NULL_POINTER_ERROR)
    {
        printf("Invalid result pointer.\n");
        return 0;
    }

    // Read the destination base.
    printf("Enter destination base: ");

    scanStatus = scanf("%31s", destinationInput);

    if (scanStatus == EOF)
    {
        printf("Unexpected end of input.\n");
        return 0;
    }

    if (scanStatus != 1)
    {
        cleanInputLine();
        printf("Invalid input.\n");
        return 0;
    }

    status = cleanInputLine();

    if (status == -1)
    {
        printf("Unexpected end of input.\n");
        return 0;
    }

    if (status == 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    // Parse the destination base safely.
    errno = 0;
    parsedDestination = strtol(destinationInput, &endptr, 10);

    if (errno == ERANGE || endptr == destinationInput || *endptr != '\0')
    {
        printf("Invalid destination base input.\n");
        return 0;
    }

    if (!isValidBase(parsedDestination))
    {
        printf("Invalid destination base. Please enter 2, 8, 10, or 16.\n");
        return 0;
    }

    destinationBase = (int)parsedDestination;

    // Display the result.
    printf("\nDecimal: %lld\n", result);

    printf("Converted value in base %d: ", destinationBase);

    decimalToBase(result, destinationBase);

    return 0;
}
