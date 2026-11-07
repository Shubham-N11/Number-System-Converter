#include <stdio.h>
void decimalToBinary(int num)
{
    int remain = 0, binary[32];
    int i=0;
    
    printf("Decimal to Binary is :\n");
    
    while (num > 0)
    {
        remain = num % 2;
        binary[i] = remain;
        num = num / 2;
        i++;
    }
    
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%d", binary[j]);
    }
}

void decimalToOctal(int num)
{
    int remain = 0, octal[32];
    int i=0;
    
    printf("Decimal to Octal is :\n");

    while (num > 0)
    {
        remain = num % 8;
        octal[i] = remain;
        num = num / 8;
        i++;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        printf("%d", octal[j]);
    }
}

int main()
{
    int num;
    printf("Enter decimal: ");
    scanf("%d", &num);
    
    if(num <= 0)
    {
        printf("Please enter a positive integer.");
        return 0;
    }
    else if(num == 0)
    {
        printf("0");
        return 0;
    }

    // decimalToBinary(num);
    decimalToOctal(num);
}