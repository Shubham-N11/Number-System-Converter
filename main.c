#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

void decimalToBase(long long decimal, int destinationBase)
{
    int remain = 0;
    char output[65];
    int i = 0;

    printf("Converted value in base %d is :\n", destinationBase);

    if (decimal == 0)
    {
        printf("0");
        return;
    }

    while (decimal > 0)
    {
        remain = decimal % destinationBase;
        if (remain > 9)
        {
            switch (remain)
            {
            case 10:
                remain = 'A';
                break;
            case 11:
                remain = 'B';
                break;
            case 12:
                remain = 'C';
                break;
            case 13:
                remain = 'D';
                break;
            case 14:
                remain = 'E';
                break;
            case 15:
                remain = 'F';
                break;
            }
        }
        else
        {
            remain = '0' + remain;
        }
        output[i] = remain;
        decimal = decimal / destinationBase;
        i++;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        printf("%c", output[j]);
    }
}

long long baseToDecimal(char num[], int base)
{
    long long decimal = 0;
    int digit;

    for (int i = 0; num[i] != '\0'; i++)
    {
        // Identify the digit
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
            printf("Invalid character.");
            return -1;
        }

        // Validate digit against the source base
        if (digit >= base)
        {
            printf("Invalid digit for the given base.");
            return -1;
        }

        // Check integer overflow before calculation
        if (decimal > (LLONG_MAX - digit) / base)
        {
            printf("Integer overflow detected.");
            return -1;
        }

        // Convert the current digit
        decimal = decimal * base + digit;
    }

    return decimal;
}

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

int main()
{
    char num[32];
    int base;
    long long result = 0;
    int destinationBase;
    int status;

    printf("Enter number : ");

    if (scanf("%31s", num) != 1)
    {
        cleanInputLine();
        printf("Invalid input.");
        return 0;
    }

    status = cleanInputLine();

    if (status == -1)
    {
        printf("Unexpected end of input.");
        return 0;
    }

    if (status == 0)
    {
        printf("Invalid input.");
        return 0;
    }

    printf("Enter base : ");

    if (scanf("%d", &base) != 1)
    {
        cleanInputLine();
        printf("Invalid input.");
        return 0;
    }

    status = cleanInputLine();

    if (status == -1)
    {
        printf("Unexpected end of input.");
        return 0;
    }

    if (status == 0)
    {
        printf("Invalid input.");
        return 0;
    }

    if (base != 2 && base != 8 && base != 10 && base != 16)
    {
        printf("Invalid base. Please enter 2, 8, 10, or 16.");
        return 0;
    }

    if (num[0] == '-')
    {
        printf("Negative numbers are not supported.");
        return 0;
    }

    result = baseToDecimal(num, base);

    if (result == -1)
    {
        return 0;
    }

    printf("Enter destination base: ");

    if (scanf("%d", &destinationBase) != 1)
    {
        cleanInputLine();
        printf("Invalid input.");
        return 0;
    }

    status = cleanInputLine();

    if (status == -1)
    {
        printf("Unexpected end of input.");
        return 0;
    }

    if (status == 0)
    {
        printf("Invalid input.");
        return 0;
    }

    if (destinationBase != 2 && destinationBase != 8 && destinationBase != 10 && destinationBase != 16)
    {
        printf("Invalid destination base.");
        return 0;
    }

    printf("Decimal: %lld\n", result);
    decimalToBase(result, destinationBase);
}