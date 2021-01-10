#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Ask for Name then print out Hello, Name
    printf("Hello, %s\n", get_string("What's your name?\n"));
}