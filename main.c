#include <stdio.h>
#include <string.h>
#include <limits.h>

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
    long long power = 1;
    long long term;
    int digit;

    for (int i = strlen(num) - 1; i >= 0; i--)
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
            printf("Invalid character");
            return -1;
        }

        if (digit >= base)
        {
            printf("Invalid digit for the given base.");
            return -1;
        }

        // Check multiplication overflow
        if (digit != 0 && power > LLONG_MAX / digit)
        {
            printf("Integer overflow detected.");
            return -1;
        }

        term = digit * power;

        // Check addition overflow
        if (decimal > LLONG_MAX - term)
        {
            printf("Integer overflow detected.");
            return -1;
        }

        decimal += term;

        // Check positional power overflow
        if (i > 0 && power > LLONG_MAX / base)
        {
            printf("Integer overflow detected.");
            return -1;
        }

        if (i > 0)
        {
            power *= base;
        }
    }

    return decimal;
}

int main()
{
    char num[32];
    int base;
    long long result = 0;
    int destinationBase;

    printf("Enter number : ");

    if (scanf("%31s", num) != 1)
    {
        printf("No input provided.");
        return 0;
    }

    printf("Enter base : ");

    if (scanf("%d", &base) != 1)
    {
        printf("Invalid input");
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

    // decimalToBinary(num);
    // decimalToOctal(num);
    // decimalToHexadecimal(num);
    // decimalToBase(decimal, destinationBase);
    result = baseToDecimal(num, base);

    if (result == -1)
    {
        return 0;
    }

    printf("Enter destination base: ");

    if (scanf("%d", &destinationBase) != 1)
    {
        printf("Invalid input");
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