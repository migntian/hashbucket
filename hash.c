#include <stdio.h>
#include "hash.h"
//哈希桶
void HashInit(HashTable *ht,HashFunc hash_func)
{
    if(ht == NULL)
    {
        return;
    }
    ht->size = 0;
    ht->func = hash_func;
    size_t i = 0;
    for(;i < HASHMAXSIZE;i++)
    {
        ht->data[i] = NULL;
    }
    return;
}
int HashFuncDefault(keytype key)
{
    return key % HASHMAXSIZE;
}
HashElem *creat(keytype key,valtype value)
{
    HashElem *newnode = (HashElem *)malloc(sizeof(HashElem));
    newnode->key = key;
    newnode->value = value;
    newnode->next = NULL;
    return;
}
void HashInsert(HashTable *ht,keytype key,valtype value)
{
    if(ht == NULL)
    {
        return;
    }
    int offset = HashFuncDefault(key);
    HashElem* cur = ht->data[offset];
    while(1)
    {
        while(cur != NULL)
        {
            if(cur->key = key)
            {
                return;
            }
            cur = cur->next;
        }
        HashElem *newnode = creat(key,value);
        newnode ->next = ht->data[offset];
        ht->data[offset] = newnode;
        ht->size++;
        return;
    }
    ++ht->size;
    return;
}
int HashFind(HashTable *ht,keytype key,valtype *value,HashElem **pre)
{
    if(ht == NULL)
    {
        return 0;
    }
    int offset = HashFuncDefault(key);
    HashElem* cur = ht->data[offset];
    HashElem *prev = NULL;
    while(cur != NULL)
    {
        if(cur->key == key)
        {
            *value = cur->value;
            *pre = prev;
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
    
}
void HashRemove(HashTable *ht,keytype key)
{
    if(ht == NULL)
    {
        return;
    }
    int offset = HashFuncDefault(key);
    HashElem* cur = ht->data[offset];
    HashElem *pre = NULL;
    valtype value;
    int ret = HashFind(ht,key,&value,&pre);
    if(ret == 1)
    {
        while(cur != NULL)
        {
            if(cur->value == ht->data[offset]->value)
            {
                ht->data[offset] = cur->next;
                free(cur);
                return;
            }
            else
            {
                pre->next = cur->next;
                free(cur);
                return;
            }
        }
    }
    return;
}
void Hashdestroy(HashTable *ht)
{
    if(ht == NULL)
    {
        return;
    }
    size_t i = 0;
    for(;i < HASHMAXSIZE;i++)
    {
        ht->data[i] = NULL;
    }
    return;
}
///////
//test
///////
#define HEADER printf("\n==========%s==========\n",__FUNCTION__)
void Hashprint(HashTable *ht)
{
    if(ht == NULL)
    {
        return;
    }
    size_t i = 0;
    for(;i < HASHMAXSIZE;i++)
    {
        HashElem* cur = ht->data[i];
        while(cur != NULL) {
            printf("%d [%d|%d]  ",i, cur->key, cur->value);
            cur = cur->next;
        }
    }
    printf("\n");
}
void testinsert()
{
    HEADER;
    HashTable hash;
    HashInit(&hash,HashFuncDefault);
    HashInsert(&hash,1,1);
    HashInsert(&hash,2,2);
    HashInsert(&hash,2,10);
    HashInsert(&hash,11,11);
    HashInsert(&hash,12,12);
    Hashprint(&hash);

}
void testfind()
{
    HEADER;
    HashTable hash;
    HashInit(&hash,HashFuncDefault);
    HashInsert(&hash,1,1);
    HashInsert(&hash,2,2);
    HashInsert(&hash,2,10);
    HashInsert(&hash,11,11);
    HashInsert(&hash,12,12);
    Hashprint(&hash);
    valtype value;
    HashElem *pre;
    int ret = HashFind(&hash,11,&value,&pre);
    printf("expected is 1 ,actul is %d\n",ret);
    printf("expected is 11 ,actul is %d\n",value);

}
void testremove()
{
    HEADER;
    HashTable hash;
    HashInit(&hash,HashFuncDefault);
    HashInsert(&hash,1,1);
    HashInsert(&hash,2,2);
    HashInsert(&hash,2,10);
    HashInsert(&hash,11,11);
    HashInsert(&hash,12,12);
    Hashprint(&hash);
    HashRemove(&hash,2);
    Hashprint(&hash);
    //valtype value;
    //int ret = HashFind(&hash,11,&value);
    //printf("expected is 1 ,actul is %d\n",ret);

}
int main()
{
    testinsert();
    testfind();
    testremove();
    return 0;
}
