// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include<stdlib.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// keep the track on words
unsigned int csize = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    int ckey = hash(word);

    for (node *cursor = table[ckey] ; cursor != NULL ; cursor = cursor->next){

        if(strcasecmp(word , cursor->word) == 0){

            return true;
        }
    }
    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int g = 31;
    int sum = 0;
    int value;

    for(int i = 0 ; word[i] != '\0' ; i++){

        sum = g * sum + tolower(word[i]);

    }

    value = sum % N;

    return value;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
   int key = 0;
   table[key] = NULL;
   char w[LENGTH + 1];

   //opening a new file
   FILE *file = fopen(dictionary , "r");

   if(file == NULL){

    printf("file wont open");
    return false;

   }

   while (fscanf(file , "%s", w) != EOF){

        //creating new node
        node *n = malloc(sizeof(node));

        if ( n == NULL){

            printf("no memory");
            return false;
        }

        strcpy(n->word, w);        //assigning a word to the new node
        n->next = NULL;
        key = hash(n->word);        // hashing the word

        if (table[key] != NULL){

            n->next = table[key];     //if word already exist in the hash table
            table[key] = n;           //inserting new node
            csize++;
        }

        else{
            table[key] = n;               //if no word is in the hash table
            csize++;
        }


   }
     //closing the file after being loaded
     fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return csize;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0 ; i <= 26 ; i++){

        node *temp = table[i];

        while (temp != NULL){

            node *cursor = temp->next;
            free(temp);                                          //freeing each every node in memory
            temp = cursor;
        }



    }

    return true;
}
