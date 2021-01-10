#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Assign key
    string key = argv[1];

    //Check if user enters a single key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //Check if user enters a 26-character key
    else if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //Check if user enters an alphabetic key
    for (int i = 0; i < strlen(key); i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    //Check for duplicate characters in the alphabetic key
    for (int j = 0; j < (strlen(key) - 1); j++)
    {
        for (int k = j + 1; k < strlen(key); k++)
        {
            if (key[j] == key[k])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    //Prompt for plaintext input and pre-define ciphertest
    string plaintext = get_string("plaintext: ");

    char ciphertext[strlen(plaintext)];

    for (int o = 0; o < strlen(plaintext); o++)
    {
        ciphertext[o] = plaintext[o];
    }

    //Define standard alphabet all in lower case
    string alphabet = "abcdefghijklmnopqrstuvwxyz\n";

    //Define an all lower case key
    char lowerkey[strlen(alphabet)];

    for (int n = 0; n < strlen(key); n++)
    {
        lowerkey[n] = tolower(key[n]);
    }

    //Find position of each letter in plaintext in alphabet, then find the according letter in lowerkey and assign it to ciphertext
    for (int l = 0; l < strlen(plaintext); l++)
    {  
        if (isalpha(ciphertext[l]))
        {
            for (int m = 0; m < strlen(lowerkey); m++)
            {
                if (tolower(plaintext[l]) == alphabet[m])
                {
                    if (islower(ciphertext[l]))
                    {
                        ciphertext[l] = lowerkey[m];
                    }
                    else
                    {
                        ciphertext[l] = toupper(lowerkey[m]);
                    }
                }
            }
        }
    }

    //Print result
    ciphertext[strlen(plaintext)] = '\0';
    printf("ciphertext: %s\n", ciphertext);
    return 0;

}