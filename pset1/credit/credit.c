#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //get card number
    long card = get_long("Number: ");

    int digit1, digit2, product;
    int sum = 0;
    long cardnumber1 = card / 10;
    long cardnumber2 = card;

    while (cardnumber1 > 0)
    {
        digit1 = cardnumber1 % 10;

        if (digit1 * 2 >= 10)
        {
            sum = sum + (digit1 * 2) / 10 % 10 + (digit1 * 2) % 10;
        }
        else
        {
            sum = sum + (digit1 * 2) % 10;
        }
        //printf("%i\n", digit1);
        cardnumber1 = cardnumber1 / 100;
        //printf("%ld\n", cardnumber1);
    }

    while (cardnumber2 > 0)
    {
        digit2 = cardnumber2 % 10;
        sum = sum + digit2;
        cardnumber2 = cardnumber2 / 100;
        //printf("%ld\n", cardnumber2);
        //printf("%i\n", sum);
    }

    //printf("%i\n", sum);

    if ((sum % 10 == 0) && (card / 1000000000000000 == 0) && ((card / 10000000000000 == 34) || (card / 10000000000000 == 37)))
    {
        printf("AMEX\n");
    }
    else if ((sum % 10 == 0) && (card / 10000000000000000 == 0) && ((card / 100000000000000 == 51) || (card / 100000000000000 == 52)
             || (card / 100000000000000 == 53) || (card / 100000000000000 == 54) || (card / 100000000000000 == 55)))
    {
        printf("MASTERCARD\n");
    }
    else if ((sum % 10 == 0) && (((card / 10000000000000 == 0) && (card / 1000000000000 == 4)) || ((card / 10000000000000000 == 0)
                                 && (card / 1000000000000000 == 4))))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}