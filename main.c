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

void decimalToHexadecimal(int num)
{
    int remain = 0;
    char hexadecimal[32];
    int i=0;
    
    printf("Decimal to Hexadecimal is :\n");
    
    while (num > 0)
    {
        remain = num % 16;
        if(remain > 9)
        {
            switch(remain)
            {
                case 10 :
                remain = 'A';
                break;
                case 11 :
                remain = 'B';
                break;
                case 12 :
                remain = 'C';
                break;
                case 13 :
                remain = 'D';
                break;
                case 14 :
                remain = 'E';
                break;
                case 15 :
                remain = 'F';
                break;
            }
        }
        else
        {
            remain = remain + '0';
        }
        
        hexadecimal[i] = remain;
        num = num / 16;
        i++;
    }
    
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%c", hexadecimal[j]);
    }
}

void decimalToBase(int num, int base)
{
    int remain = 0;
    char output[32];
    int i=0;
    
    printf("Decimal to Base %d is :\n", base);

    while (num > 0)
    {
        remain = num % base;
        if(remain > 9)
        {
            switch(remain)
            {
                case 10 :
                    remain = 'A';
                    break;
                case 11 :
                    remain = 'B';
                    break;
                case 12 :
                    remain = 'C';
                    break;
                case 13 :
                    remain = 'D';
                    break;
                case 14 :
                    remain = 'E';
                    break;
                case 15 :
                    remain = 'F';
                    break;
            }
        }
        else
        {
            remain = '0' + remain;
        }
        output[i] = remain;
        num = num / base; 
        i++;
    }
    
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%c", output[j]);
    }
}

int main()
{
    int num, base;
    printf("Enter decimal: ");
    scanf("%d", &num);
    printf("Enter base: ");
    scanf("%d", &base);
    
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
    // decimalToOctal(num);
    // decimalToHexadecimal(num);
    decimalToBase(num, base);
}