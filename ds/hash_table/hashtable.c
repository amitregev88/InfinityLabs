/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 04/7/22 
* OL124 Implementation of Hash table
*******************************************************************/

#include <assert.h>
#include <stdlib.h> /*malloc */ 
#include "dlinked_list.h"
#include "hashtable.h"
#include <stdio.h>

struct hashtable
{
    compare_ty cmp;

    ht_func_ty ht_func;

    size_t size_ht;

    size_t num_of_elem;

    dlist_ty **ht_arr_of_ptr;
};

static int IsValidIndex(const ht_ty *ht, int index);

/*Function creates a new hashtable sata structure
return NULL if malloc fails */
ht_ty *HTCreate(compare_ty compare,ht_func_ty hashfunction,size_t hashTableSize)
{
    ht_ty *new_ht = NULL;

    int i = 0;

    assert(compare);
    assert(hashfunction);
    assert(hashTableSize > 0);
        
    new_ht = (ht_ty *)malloc(sizeof(ht_ty) + (hashTableSize * sizeof(dlist_ty *)));
    if (!new_ht)
    {
        return NULL;
    }

    new_ht->ht_arr_of_ptr = (dlist_ty **)((char *)new_ht + sizeof(ht_ty));
    new_ht->cmp = compare;
    new_ht->ht_func = hashfunction;
    new_ht->size_ht = hashTableSize;
    new_ht->num_of_elem = 0;

    for(i = 0; i < (int)hashTableSize; ++i)
    {
        new_ht->ht_arr_of_ptr[i] = DListCreate();

        if (!new_ht->ht_arr_of_ptr[i])
        {
            for (i = i - 1; i >= 0 ; --i)
            {
                free(new_ht->ht_arr_of_ptr[i]);
            }

            free(new_ht);

            new_ht = NULL; 
        }      
    }
        
    return new_ht;
}

/*Function frees all the elements in the hashtable*/
void HTDestroy(ht_ty* ht)
{
    size_t i = 0;
    assert(ht);
 
    for(i = 0; i < ht->size_ht; ++i)
    {
        DListDestroy(ht->ht_arr_of_ptr[i]);
    }        
   
    free(ht);
}

/*Function returns the number of items stored in HashTable*/
size_t HTSize(const ht_ty *ht)
{
    assert(ht);
    return (ht->num_of_elem); 
}

/*Return 1 - is Empty, 0 - not Empty*/
int HTIsEmpty(const ht_ty *ht)
{
    assert(ht);
    return (ht->num_of_elem == 0);
}

/*If fail return 0 else 1 */
int HTInsert(ht_ty *ht, void *data)
{
    int index = 0;

    assert(ht);
    assert(data);

    index = ht->ht_func(data);

    if (!IsValidIndex(ht, index))
    {
        return 1;
    }

    if(HTFind(ht, data))
    {
        return 1;
    }

    if (DListPushFront(ht->ht_arr_of_ptr[index], data) != NULL)
    {
        ++ht->num_of_elem;
        return 0;
    }

    return 1;
}

/*Returns pointer to val to remove */
void* HTRemove(ht_ty *ht , void *data)
{	
	int index = 0;
	void *data_to_remove = NULL;
	dlist_node_ty *to_remove = NULL;

	assert(ht);
	assert(data);

    index = ht->ht_func(data);

    if(IsValidIndex(ht,index) == 0)
    {
        return NULL;
    }
	
	to_remove = DListFind(DListBegin(ht->ht_arr_of_ptr[index]), DListEnd(ht->ht_arr_of_ptr[index]), ht->cmp, data);

	data_to_remove = DListGetData(to_remove);

	DListRemove(to_remove);

    --ht->num_of_elem;

	return data_to_remove;
}

/*Find data in ht according to the compare function and returns pointer to val.*/
void* HTFind(const ht_ty *ht, void *data)
{
    int index = 0;

    dlist_node_ty *find_node = NULL; 
    void *find_res = NULL;
    
    assert(ht);
    assert(data);

    index = ht->ht_func(data);

    if (!IsValidIndex(ht,index))
    {
        return NULL;
    }

    find_node = DListFind(DListBegin(ht->ht_arr_of_ptr[index]),DListEnd(ht->ht_arr_of_ptr[index]),ht->cmp,data); 
    if (find_node)
    {
        find_res = DListGetData(find_node);
    }

    return find_res;
}

/*If action function fail -  return 0 else 1 */
int HTForeach(const ht_ty *ht,int (*action)(void *val, const void *param), const void *param)
{
    size_t i = 0;
    int res = 0;

    assert(ht);
    assert(action);
   
    for (i = 0; i < ht->size_ht; i++)
    {
        if (!DListIsEmpty(ht->ht_arr_of_ptr[i]))
        {
            res += DListForEach(DListBegin(ht->ht_arr_of_ptr[i]),DListEnd(ht->ht_arr_of_ptr[i]),action, param);
        } 
    }

    return res;
}

static int IsValidIndex(const ht_ty *ht, int index)
{
    if (index < 0 || index >= (int)ht->size_ht)
    {
        return 0;
    }

    return 1;
}

void HTDestroyTotally(ht_ty *ht)
{
	size_t i = 0;
	void *to_remove = NULL;

	assert(ht);

	for(i = 0; i < ht->size_ht; ++i)
	{
		while (!DListIsEmpty(ht->ht_arr_of_ptr[i]))
		{
			to_remove = DListPopBack(ht->ht_arr_of_ptr[i]);
			free(to_remove);
		}
		DListDestroy(ht->ht_arr_of_ptr[i]);
	}
	free(ht->ht_arr_of_ptr);
	free(ht);
}
