// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000;
unsigned int dic_word_count = 0;

// Hash table
node *table[N + 1];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int hash_value = hash(word);
    node *list = table[hash_value];

    for (node *cursor = list; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash_value = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_value += toupper(word[i]);
    }
    hash_value %= N;
    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    {
        dic_word_count++;

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            fclose(source);
            return false;
        }

        strcpy(n->word, word);
        n->next = NULL;

        unsigned int hash_value = hash(word);

        node *list = table[hash_value];

        if (list == NULL)
        {
            list = n;
        }
        else
        {
            n->next = list;
            list = n;
        }

        table[hash_value] = list;
    }
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dic_word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *list = table[i];
        node *cursor = list;
        while (cursor != NULL)
        {
            node *next = cursor->next;
            free(cursor);
            cursor = next;
        }
    }
    return true;
}
