#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //get card number
    long card = get_long("Number: ");

    long cardnumber1 = card / 10;
    long cardnumber2 = card;

    printf("%ld\n", cardnumber1);
    printf("%ld\n", cardnumber2);
    printf("%f\n", card / pow(10,15));
    printf("%f\n", card / pow(10,16));
    printf("%ld\n", card / 100000000000000);
}