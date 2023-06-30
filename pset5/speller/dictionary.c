// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int size_of_dict = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 27 * 27 * 27 * 27; //first four letters

// Hash table
node *table[N];
//that means every index in the table points to a node, so to access the address wed say table[i] and not table[i]->next

// Returns true if word is in dictionary else false
bool check(const char *word) //omg it works
{
    node *index = table[hash(word)];
    while (index != NULL)
    {
        if (strcasecmp(word, index->word) == 0) //compare it to each word in the index
        {
            return true;
        }
        else
        {
            index = index->next; //go to the next one
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) //this is good too
{
    char *Word = malloc(LENGTH + 1);
    //make it all lowercase
    for (int i = 0; i < LENGTH; i++)
    {
        if (word[i] != '\0')
        {
            Word[i] = tolower(word[i]);
        }
        else
        {
            Word[i] = '\0';
            break;
        }
    }

    int k = 0;
    for (int i = 0; i < 4; i++)
    {
        if ('a' <= Word[i] && Word[i] <= 'z') //if it's a letter
        {
            k = k + pow(27, 3 - i) * (Word[i] - 97);
        }
        else if (Word[i] == 39) //if its an apostrophe
        {
            k = k + pow(27, 3 - i) * 26;
        }
        else if (Word[i] == '\0')
        {
            free(Word);
            return k;
        }
    }
    free(Word);
    return k;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary) //ok this is good
{
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char *wordx = malloc(LENGTH + 1);

    if (wordx == NULL)
    {
        return false;
    }

    int x = 0; //while loop condition
    while (x == 0)
    {
        if (fscanf(f, "%s", wordx) == EOF) //once we've reached end of file
        {
            fclose(f);
            free(wordx);
            return true;
        }

        node *newword = malloc(sizeof(node));
        strcpy(newword->word, wordx);
        int i = hash(newword->word);

        //insert new node into table
        if (table[i] == NULL)
        {
            newword->next = NULL;
            table[i] = newword;
            size_of_dict++;
        }
        else
        {
            newword->next = table[i];
            table[i] = newword;
            size_of_dict++;
        }
    }
    free(wordx);
    fclose(f);
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return size_of_dict;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void) //ok this is the problem
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        node *index = table[i];
        node *indexfree = table[i];
        while (index != NULL)
        {
            index = index->next;
            free(indexfree);
            indexfree = index;
        }
    }
    return true;
}
// use this to check ./speller texts/asdkfjas;dfaj.txt