// =================== Support Code =================
// Hashmap
//
// - Implement each of the functions to create a working hashmap.
// - Do not change any of the function declarations
//   - (i.e. hashmap_t* hashmap_create() should not have additional arguments)
// - You should not have any 'printf' statements in your functions other
//   than functions that explicitly ask for printf  output.
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// - You may add any helper functions that you think you need (if any, or otherwise for debugging)
// ==================================================

// CS 5008 Assignment 4
// Author: Nianlong Lin
// Date: 2023/09/23

#ifndef MY_HASHMAP_T
#define MY_HASHMAP_T

#include <stdlib.h>
#include <string.h>


// A key value pair
// This is specifically for a (char*, char*) key value pair
typedef struct pair{
    char* key;
    char* value;
}pair_t;

// Each node holds a key and a value
typedef struct node{
    struct node* next;
    pair_t* kv;          // 'kv' stands for key/value pair
}node_t;


// Simple hash function that will put a key into a bucket
// You should not modify this
int stringHash(char* myKey, int numberOfBuckets){
    return strlen(myKey) % numberOfBuckets;
}

// Create a function prototype to a function that takes
// in a char* and an int.
typedef int(*hashFunctionPointer)(char*,int) ;

// Chained implementation of a hashmap
typedef struct hashmap{
    unsigned int buckets;   // i.e. size of the hashmap
    node_t** arrayOfLists;  // An array of linked lists for our buckets
                            // Read another way
                            //      - an array of node_t*

    // A function pointer to a hash function
    // The hash_function must take in a 'char*' as a key, and have a
    // second parameter specifying the number of buckets.
    hashFunctionPointer hashFunction;
}hashmap_t;

// Creates a new hashmap
// Allocates memory for a new hashmap.
// Initializes the capacity(i.e. number of buckets)
hashmap_t* hashmap_create(unsigned int _buckets){
    // Allocate memory for our hashmap
	hashmap_t* new_map = (hashmap_t*)malloc(sizeof(hashmap_t));
    // Set the number of buckets
	new_map->buckets = _buckets;
    // Initialize our array of lists for each bucket
	new_map->arrayOfLists = (node_t**)malloc(sizeof(node_t*) * _buckets);
    for (int i = 0; i < _buckets; i++) {
        new_map->arrayOfLists[i] = NULL;
    }
    // Setup our hashFunction to point to our
    // stringHash function.
	new_map->hashFunction = &stringHash;
    // Return the new map that we have created
    return new_map;
}

// Frees a hashmap
// Responsibility to free a hashmap that has been previously allocated.
// Must also free all of the chains in the hashmap
// This function should run in O(n) time
void hashmap_delete(hashmap_t* _hashmap){
    if (_hashmap != NULL) {
        for (int i = 0; i < _hashmap->buckets; i++) {
            node_t* current_node = _hashmap->arrayOfLists[i];
            while (current_node != NULL) {
                node_t* next_node = current_node->next;
                free(current_node->kv->key);
                free(current_node->kv->value);
                free(current_node->kv);
                current_node = next_node;
            }
        }
        free(_hashmap->arrayOfLists);
        free(_hashmap);
    }
}

// Returns a boolean value if a key has been put into
// the hashmap
//  - Returns a '1' if a key exists already
//  - Returns a '0' if the key does not exist
//  - Returns a '-9999' if the hashmap is NULL
// The algorithm is:
//  - Call the _hashmap's hash function on the key
//  - Search that bucket to see if the key exists.
// This function should run in average-case constant time
int hashmap_hasKey(hashmap_t* _hashmap, char* key){

    if (_hashmap == NULL) {
        return -9999;
    }
    int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
    node_t* current_node = _hashmap->arrayOfLists[bucket];
    while (current_node != NULL) {
        if (strcmp(current_node->kv->key, key) == 0) {
            return 1;
        }
        current_node = current_node->next;
    }
    return 0;

}

// Insert a new key/value pair into a hashmap
// The algorithm is:
//  - If a key already exists, do not add it--return
//  - Call the _hashmap's hash function on the key
//  - Store the key/value pair at the end of the buckets chain
//      - You should malloc the key/value in this function
// This function should run in average-case constant time
void hashmap_insert(hashmap_t* _hashmap,char* key,char* value){

    if (hashmap_hasKey(_hashmap, key) == 1) {
        return;
    }

    int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->kv = (pair_t*)malloc(sizeof(pair_t));
    new_node->kv->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
    new_node->kv->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(new_node->kv->key, key);
    strcpy(new_node->kv->value, value);
    new_node->next = _hashmap->arrayOfLists[bucket];
    _hashmap->arrayOfLists[bucket] = new_node;

}

// Return a value from a key
// Returns NULL if the key is not found
// The algorithm is:
//  - If the key does not exist, then--return NULL if not found.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and return the value
// This function should run in average-case constant time
char* hashmap_getValue(hashmap_t* _hashmap, char* key){
    if (_hashmap == NULL) {
        return NULL;
    }
    int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
    node_t* current_node = _hashmap->arrayOfLists[bucket];
    while (current_node != NULL) {
        if (strcmp(current_node->kv->key, key) == 0) {
            return current_node->kv->value;
        }
        current_node = current_node->next;
    }
    return NULL;
}

// TODO NOTE THAT I DID NOT FINISH REMOVE KEY BECAUSE...
// Remove a key from a hashmap
// The algorithm is:
//  - Determine if the key exists--return if it does not.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and then remove it
// This function should run in average-case constant time
void hashmap_removeKey(hashmap_t* _hashmap, char* key){
	if (_hashmap == NULL) {
        return;
	}

	int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* current_node = _hashmap->arrayOfLists[bucket];
	node_t* previous_node = NULL;
	while (current_node != NULL) {
        if (strcmp(current_node->kv->key, key) == 0) {
            if (previous_node == NULL) {
                _hashmap->arrayOfLists[bucket] =  current_node->next;
            } else {
                previous_node->next = current_node->next;
            }
            free(current_node->kv->key);
            free(current_node->kv->value);
            free(current_node->kv);
            free(current_node);
            return;
        }
        previous_node = current_node;
        current_node = current_node->next;
	}
}

// Update a key with a new Value
// The algorithm is:
//  - Returns immediately if the key does not exist
//  - Call the _hashmap's hash function on the key
//  - Updates the value of the key to the new value
// This function should run in average-case constant time
void hashmap_update(hashmap_t* _hashmap, char* key, char* newValue){
    if (_hashmap == NULL) {
        return;
    }

    int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
    node_t* current_node = _hashmap->arrayOfLists[bucket];
    while (current_node != NULL) {
        if (strcmp(current_node->kv->key, key) == 0) {
            free(current_node->kv->value);
            current_node->kv->value = (char*)malloc(sizeof(char) * (strlen(newValue) + 1));
            strcpy(current_node->kv->value, newValue);
            return;
        }
        current_node = current_node->next;
    }
}

// Prints all of the keys in a hashmap
// The algorithm is:
//  - Iterate through every bucket and print out the keys
// This function should run in O(n) time
void hashmap_printKeys(hashmap_t* _hashmap){
	if (_hashmap == NULL) {
        return;
	}
	for (int i = 0; i < _hashmap->buckets; i++) {
        node_t* current_node = _hashmap->arrayOfLists[i];
        while (current_node != NULL) {
            printf("key: %s\n", current_node->kv->key);
            current_node = current_node->next;
        }
	}
}

#endif
