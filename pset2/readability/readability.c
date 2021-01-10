#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    //predefine number of letters, words and sentences
    int letters = 0, words = 1, sentences = 0;

    //prompt user for text
    string text = get_string("Text: ");

    //calculate number of letters, words and sentences
    for (int i = 0; i < strlen(text); i++)
    {
        //check number of alphabetic letters
        if (isalpha(text[i]))
        {
            letters++;
        }

        //check if there is a non-space character after space, if yes then increase word count by 1
        if (isspace(text[i]) && ~isspace(text[i + 1]))
        {
            words++;
        }

        //check for period, exclamation point, question mark, if detected then increase sentence count by 1
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    //printf("%i letter(s)\n", letters);
    //printf("%i word(s)\n", words);
    //printf("%i sentence(s)\n", sentences);

    //calculate Coleman-Liau index
    float index = 0.0588 * (float) letters / (float) words * 100 - 0.296 * (float) sentences / (float) words * 100 - 15.8;

    //Check for reading level then print appropriate result
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}