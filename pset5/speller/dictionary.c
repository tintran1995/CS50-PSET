// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"
#include <string.h>
#include <strings.h>

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 32768;

// Hash table
node *table[N];

// Define global wordCounter
int wordCounter = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Assign word to a char array
    char wordBuffer[strlen(word) + 1];
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isupper(word[i]))
        {
            wordBuffer[i] = tolower(word[i]);
        }
        else
        {
            wordBuffer[i] = word[i];
        }
    }
    wordBuffer[strlen(word)] = '\0';

    // Check if word is in dictionary
    unsigned int hashValue;
    hashValue = hash(wordBuffer);

    if (table[hashValue] == NULL)
    {
        return false;
    }

    node *cursor = table[hashValue];
    if (cursor == NULL)
    {
        return 1;
    }

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, wordBuffer) == 0)
        {
            return true;
        }
        else
            cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
// Hash function djb2 by Dan Bernstein http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c;    /* hash * 33 + c */
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Load dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // initialise table to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char wordBuffer[LENGTH + 1];
    unsigned int hashIndex;

    while (fscanf(file, "%s", wordBuffer) != EOF)
    {
        // Create new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        n->next = NULL;
        strcpy(n->word, wordBuffer);
        hashIndex = hash(n->word);
        n->next = table[hashIndex];
        table[hashIndex] = n;
        wordCounter++;
    }

    if (feof(file))
    {
        fclose(file);
        return true;
    }
    else
    {
        fclose(file);
        return false;
    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (wordCounter != 0)
    {
        return wordCounter;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Release each index in table[N]
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        if (cursor == NULL)
        {
            continue;
        }

        while (cursor != NULL)
        {
            node *tmp = cursor;
            if (tmp == NULL)
            {
                return 1;
            }
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}