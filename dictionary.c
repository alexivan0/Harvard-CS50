// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "dictionary.h"
#include <strings.h>
#include <string.h>
#include <ctype.h>
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;
int wordsnr = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashcode = hash(word);
    node *temp = table[hashcode];
    while (temp != NULL)
    {
        if (strcasecmp(temp->word, word) != 0)
        {
            temp = temp->next;
        }
        else if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    long sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    char temp[LENGTH + 1];
    while (fscanf(file, "%s", temp) != EOF)
    {
        fscanf(file, "%s", temp);
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy (n->word, temp);
        int hashcode = hash(temp);
        n->next = table[hashcode];
        table[hashcode] = n;
        wordsnr++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordsnr;
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N ; i++)
    {
        node *temp2 = table[i];
        if (table[i] != NULL)
        {
            node *temp1 = table[i];
            while (temp2 != NULL)
            {
                temp2 = temp2->next;
                free(temp1);
                temp1 = temp2;
            }

        }
        if (temp2 == NULL && i == (N -1))
        {
            return true;
        }
    }
    return false;
}
