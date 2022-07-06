/***************************
 * OL124 hashtable project
 * hashtable.h
 * hashtable.c
 * hashtable_test.c
 * version 1.5
 ***************************/


#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stddef.h> /*size_t*/
typedef struct hashtable ht_ty;

/*
  - data1 == data2 -> return 1
  - data1 != data2 -> return 0
*/
typedef int(*compare_ty)(const void *data1,const void *data2);
typedef int (*ht_func_ty)(const void *data);

/*Function creates a new hashtable sata structure
return NULL if malloc fails */
ht_ty *HTCreate(compare_ty compare,ht_func_ty hashfunction,size_t hashTableSize);

/*Function frees all the elements in the hashtable*/
void HTDestroy(ht_ty* ht);

/*Function returns the number of items stored in HashTable*/
size_t HTSize(const ht_ty *ht);

/*Return 1 - is Empty, 0 - not Empty*/
int HTIsEmpty(const ht_ty *ht);

/*On success returns 0. If key exist returns 1, NO REPLACEMENT  */
int HTInsert(ht_ty *ht, void *data); 

/*Returns pointer to val to remove */
void* HTRemove(ht_ty *ht , void *data); 

/*Find data in HASHTABLE according to the compare function and returns pointer to val.*/
void* HTFind(const ht_ty *ht, void *data);

/*If action function success return 0  */
int HTForeach(const ht_ty *ht,int (*action)(void *data, const void *param), const void *param);


void PrintSize(ht_ty *ht, int table_size);

#endif /* __HASHTABLE_H__ */
