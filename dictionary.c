// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 531440;

// Hash table
node *table[N];

// Number of words in dictionary
int no_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int hash_code = hash(word);
    node *n = table[hash_code];
    while (n != NULL)
    {
        if (!strcasecmp(n->word, word))
        {
            return true;
        }
        else
        {
            n = n->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int code = 0;
    int len = strlen(word);
    char *wrdcpy = malloc(len + 1);
    for (int i = 0; i < len; i++)
    {
        wrdcpy[i] = tolower(word[i]);
    }
    wrdcpy[len] = '\0';
    if (len == 1)
    {
        // 0 - 25;
        code = wrdcpy[0] - 97;
        free(wrdcpy);
        return code;
    }
    code = 26;
    if (len == 2)
    {
        code += 27 * (wrdcpy[0] - 97);
        if (wrdcpy[1] != 39)
        {
            code += (wrdcpy[1] - 97);
        }
        else
        {
            code += 26;
        }
        free(wrdcpy);
        return code;
    }
    // code: (0 - 25) + (26 - 727) has been defined
    code = 728;
    if (len == 3)
    {
        code += 27 * 27 * (wrdcpy[0] - 97);
        if (wrdcpy[1] != 39)
        {
            code += 27 * (wrdcpy[1] - 97);
        }
        else
        {
            code += 27 * 26;
        }
        if (wrdcpy[2] != 39)
        {
            code += (wrdcpy[2] - 97);
        }
        else
        {
            code += 26;
        }
        free(wrdcpy);
        return code;
    }
    // code 0 - 19681 has been defined
    code = 19682;
    if (len > 3)
    {
        code += 27 * 27 * 27 * (wrdcpy[0] - 97);
        if (wrdcpy[1] != 39)
        {
            code += 27 * 27 * (wrdcpy[1] - 97);
        }
        else
        {
            code += 27 * 27 * 26;
        }
        if (wrdcpy[2] != 39)
        {
            code += 27 * (wrdcpy[2] - 97);
        }
        else
        {
            code += 27 * 26;
        }
        if (wrdcpy[3] != 39)
        {
            code += (wrdcpy[3] - 97);
        }
        else
        {
            code += 26;
        }
        free(wrdcpy);
        return code;
    }
    // code 0 - 531439 has been defined
    free(wrdcpy);
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    // Open required dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    int tmp = 0;
    // Stores number of words
    while (tmp == 0)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        n->next = NULL;
        if (fscanf(file, "%s", n->word) != EOF)
        {
            unsigned int hash_code = hash(n->word);
            n->next = table[hash_code];
            table[hash_code] = n;
            no_words++;
        }
        else
        {
            tmp++;
            free(n);
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return no_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (unsigned int i = 0; i < N; i++)
    {
        node *n = table[i];
        node *tmp = n;
        while (n != NULL)
        {
            n = n->next;
            free(tmp);
            tmp = n;
        }
    }
    return true;
}




