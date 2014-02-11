/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include "dictionary.h"


/**
 * Returns true if word is in dictionary else false.
 */
 
// make nodes for hash table
typedef struct node
{
    char word[LENGTH + 1]; // remember LENGTH is 45 (written in dictionary.h)
    struct node* next;
}
node;

// number of buckets in hash table
#define NUM_BUCKETS 143091

// global variable for size of dictionary
unsigned int dictionary_size = 0;

// make hash table
node* hashtable[NUM_BUCKETS];
 
/**
 * Returns a hash value for word, in the range [0, NUM_BUCKETS - 1]
 * Lowercases characters before hashing to be case-insensitive
 * Hash function adapted from:
 *     http://stackoverflow.com/questions/98153/#98179
 */
static int hash_word(const char* word)
{
    /* magic numbers from http://www.isthe.com/chongo/tech/comp/fnv/ */
    size_t InitialFNV = 2166136261U;
    size_t FNVMultiple = 16777619;
    
    /* Fowler / Noll / Vo (FNV) Hash */
    size_t hash = InitialFNV;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // xor the low 8 bits of the hash
        hash ^= (tolower(word[i]));

        // multply by the magic number
        hash *= FNVMultiple;
    }
    return (hash % NUM_BUCKETS);
}


bool check(const char* word)
{
    // TODO
    // find bucket in hash table where the word should be
    node* bucket = hashtable[hash_word(word)];
    
    // look at all entries in bucket to see if word exists by iterating over linked list at that index
    for (node* entry = bucket; entry != NULL; entry = entry->next)
    {
        // because words are lowercase, use strcasecmp to compare words
        if (strcasecmp(entry->word, word) == 0)
        {
            return true;
        }
    }   
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    // open dictionary file
    FILE* file = fopen(dictionary, "r");
    if(file == NULL)
    {
        return false;
    }
    
    // scan file and load the words onto hash table
    while(true)
    {
        // allocate memory for node/word
        node* new_node = malloc(sizeof(node));
        
        // if node is null, unload malloc and close file
        if (new_node == NULL)
        {
            unload();
            fclose(file);
            return false;
        }
        // read word from dictionary into node
        // if word is not successfully read from file, break out of while loop
        if (fscanf(file, "%45s", new_node->word) != 1)
        {
            free(new_node);
            break;
        }
        
        // hash word using hash function
        int hash = hash_word(new_node->word);
        
        // enter entry into beginning of the linked list in the hash table
        // current entry will point to what the hash table currently points to
        new_node->next =  hashtable[hash];
        // store in the hash table at the hash, the current entry
        hashtable[hash] = new_node;
        
        // increment size of hash table
        dictionary_size++; 
    }
    
    // check if program broke out of the while loop from error or end of file
    if(ferror(file))
    {
        unload();
        fclose(file);
        return false;
    }
    
    // close file if successful
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return dictionary_size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    // loop through all buckets in the hash table
    for (int i=0; i < NUM_BUCKETS; i++)
    {
        // for each linked list in hash table, loop over entire linked list and free each node
        node* entry = hashtable[i];
        while (entry != NULL)
        {
            // create temporary variable that stores pointer to next elem. in linked list
            node* next = entry->next;
            // free current element
            free(entry);
            // update current element to point to next element
            entry = next;
        }
    }
    return true;
}
