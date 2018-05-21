#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define HASHMAXSIZE 1000


typedef int keytype;
typedef int valtype;

typedef int(*HashFunc)(keytype key);

typedef struct HashElem{
    keytype key;
    valtype value;
    struct HashElem *next;
    struct HashElem *pre;
}HashElem;

typedef struct HashTable{
    HashElem* data[HASHMAXSIZE];
    size_t size;
    HashFunc func;
}HashTable;

void HashInit(HashTable *ht,HashFunc hash_func);
int HashFuncDefault(keytype key);
void HashInsert(HashTable *ht,keytype key,valtype value);
int HashFind(HashTable *ht,keytype key,valtype *value,HashElem **pre);
void HashRemove(HashTable *ht,keytype key);
void Hashdestroy(HashTable *ht);
