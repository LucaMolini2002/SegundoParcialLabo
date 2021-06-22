/*
 * Dictionary.h
 *
 *  Created on: 10 jun. 2021
 *      Author: Luk
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include "LinkedList.h"

struct sElement {
    struct sElement *next;
    char* key; // Ej "JUANA"
    void* value; // Ej *Empleado
};

typedef struct sElement DictElement;

typedef struct{
    int size;           /* size of the pointer table */
    int count;              /* number of elements stored */
    DictElement** table;
}Dictionary;

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MULTIPLIER (97) // seed

/* create a new empty dictionary, if the size value is 0, the default value will be used*/
Dictionary* dict_new(int size);

/* destroy a dictionary */
int dict_delete(Dictionary*);

/* insert a new key-value pair into an existing dictionary */
int dict_insert(Dictionary*, char *key, void* value);

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
void* dict_get(Dictionary*, char*key);

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void dict_remove(Dictionary*, char *key);

LinkedList* dict_getKeys(Dictionary* this);

LinkedList* dict_getValues(Dictionary* this);

LinkedList* dict_getUniqueValues(Dictionary* this);

#endif /* DICTIONARY_H_ */
