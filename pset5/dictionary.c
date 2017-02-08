/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// node* root;
// node* cursor;
int sizeOfDictionary;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    cursor = root;
    int charToTest;
    int lengthOfWord = strlen(word);
    
    for (int i = 0; i < lengthOfWord; i++)
    {
        charToTest = tolower(word[i]);

        if (cursor->children[charToTest % 27] == NULL)
        {
            return false;
        }
        else if(cursor->children[charToTest % 27] != NULL)
        {
            cursor = cursor->children[charToTest % 27];
        }
    }
    
    if (cursor->isAWord == true)
    {
        cursor = root;
        return true;
    }
    
    return false;
    
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* dictToRead = fopen(dictionary, "r");
    if (dictToRead == NULL)
    {
        printf("problem opening dictionary\n");
        return false;
    }
    
    root = calloc(1, sizeof(node));
    cursor = root;
    int c = fgetc(dictToRead);
    
    while (c != EOF)
    {
        if (c != '\n' && cursor->children[c % 27] != NULL)
        {
            cursor = cursor->children[c % 27];
        }
        else if(c != '\n' && cursor->children[c % 27] == NULL)
        {
            cursor->children[c % 27] = calloc(1, sizeof(node));
            cursor = cursor->children[c % 27];
        }
        else
        {
            cursor->isAWord = true;
            cursor = root;
            sizeOfDictionary++;
        }
        c = fgetc(dictToRead);
        if (c == EOF)
        {
            break;
        }
    }
    
    fclose(dictToRead);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return sizeOfDictionary;
}

void freeTheMemory(node* cursor)
{
    int i;
    
    for (i = 0; i < 27; i++)
    {
        if (cursor->children[i] != NULL)
        {
            freeTheMemory(cursor->children[i]);
        }
    }
    
    free(cursor);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload()
{
    freeTheMemory(cursor);
    return true;
}


// test for load dict and check
// int main(int argc, char* argv[])
// {
//     bool loadTester = load(argv[1]);
//     bool checkTester = check(argv[2]);
    
//     if (loadTester == true && checkTester == true)
//     {
//         printf("holy shit it worked...\n");
//         return 0;
//     }
//     else
//     {
//         return 1;
//     }
//     printf("failed to do anything");
//     return 1;
// }


//test for load dictionary only 
// int main(int argc, char* argv[])
// {
//     bool loadTester = load(argv[1]);
    
//     if (loadTester == true)
//     {
//         printf("holy shit it worked...\n");
//         printf("Number of words in Dictionary %i\n", sizeOfDictionary);
//         return 0;
//     }
//     else
//     {
//         return 1;
//     }
//     printf("failed to do anything");
//     printf("Number of words in Dictionary %i\n", sizeOfDictionary);
//     return 1;
// }