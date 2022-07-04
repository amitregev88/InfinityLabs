/*************************************************************
* Author: Amit Regev
* Reviewer: Alex Milys
* Date: 12/6/22 
* OL124 Binary Search Tree project
*******************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stddef.h> /* size_t */
#include "bst.h"

static void CopyIter(bst_iter_ty dest, bst_iter_ty src);
static int IsIterALeaf(bst_iter_ty iter);
static int IsIterHasTwoChildren(bst_iter_ty iter);
static int IsOnlyOneChild(bst_iter_ty iter);
static int IterSideChild(bst_iter_ty iter);

struct bst_node
{
    void *data;
    bst_node_ty *parent;
    bst_node_ty *right;
    bst_node_ty *left;
};

struct bst
{
    bst_node_ty *root;
    compare_ty cmp;
    size_t size;
         
};


/*the function creates a new binary tree sata structure
return NULL if malloc fails */
bst_ty *BSTCreate(compare_ty compare)
{
    
    bst_node_ty *dummy;
    bst_ty *new_bst = malloc(sizeof(bst_ty));
    if (new_bst == NULL)
    {
        return NULL;
    }

    dummy = malloc(sizeof(bst_node_ty));
    if (dummy == NULL)
    {
        /*clean up*/ 
        free(new_bst);
        return NULL;
    }

    assert(NULL != compare);

    dummy->data = NULL;
    dummy->left = NULL;
    dummy->right = NULL;
    dummy->parent = NULL;

    new_bst->cmp = compare;
    new_bst->size = 0;
    new_bst->root = dummy;

    return new_bst;
}

/* the function frees all the alements in the tree*/
void BSTDestroy(bst_ty* bst)
{
  	bst_iter_ty iter = {NULL};

	assert(bst);


	while (bst->size > 0)
	{
	    iter = BSTBegin(bst);

		BSTRemove(bst,iter);

	}


	free(bst->root); /* free dummy */
    iter.iter_node = NULL;

	free(bst);
    bst = NULL;
}


/*the function returns the number of items stored in BST*/
size_t BSTSize(const bst_ty *bst)
{
    assert(bst);
    return bst->size;

}

/*1- is Empty, 0- not Empty*/
int BSTIsEmpty(const bst_ty *bst)
{
    assert(bst);

    return (bst->size == 0);

}

/*if fail return NULL */
bst_iter_ty BSTInsert(bst_ty *bst, void *data)
{
    bst_iter_ty iter = {NULL};
    bst_iter_ty new_elem = {NULL};
    
    assert(bst);
    assert(data);
    /*assert(!BSTIter_Is_Equal(BSTFind(bst,data),iter))*/




    iter.iter_node = bst->root;
    new_elem.iter_node = malloc(sizeof(bst_node_ty));
    if (!new_elem.iter_node)
    {
        return new_elem;
    }

    new_elem.iter_node->data = data;
    new_elem.iter_node->left = NULL;
    new_elem.iter_node->right = NULL;
    new_elem.iter_node->parent = NULL;

    bst->size++;

    if (BSTSize(bst) == 1)
    {
        new_elem.iter_node->right = bst->root;
        
        bst->root->parent = new_elem.iter_node; 

        bst->root = new_elem.iter_node;

        return new_elem;
    }

    if (bst->cmp(data,BSTGet_Data(BSTPrev(BSTEnd(bst)))) == 1)  
    {
        bst_node_ty *dummy_node = BSTEnd(bst).iter_node;

		dummy_node->parent->right = new_elem.iter_node;

   		new_elem.iter_node->parent = dummy_node->parent;

        dummy_node->parent = new_elem.iter_node;

		new_elem.iter_node->right = dummy_node;
 
		return new_elem;	
	}


     
    while(1)
    {
        if(bst->cmp(data, BSTGet_Data(iter)) == 1)
        {

            if(iter.iter_node->right == NULL)
            {
                iter.iter_node->right = new_elem.iter_node; 
                new_elem.iter_node->parent = iter.iter_node;
                break;
            }
            iter.iter_node = iter.iter_node->right;
        }

        else if (bst->cmp(data, BSTGet_Data(iter)) == -1)
        {

             if(iter.iter_node->left == NULL)
            {
                iter.iter_node->left = new_elem.iter_node; 
                new_elem.iter_node->parent = iter.iter_node;
                break;
            }
            iter.iter_node = iter.iter_node->left;
        }

        else
        {
            iter.iter_node = NULL;

            free(new_elem.iter_node);
            new_elem.iter_node = NULL;

            --bst->size;

            return iter; 

        }    
    
    }

    return new_elem;
}


/* removes node. returns iter's data */
void *BSTRemove(bst_ty *bst , bst_iter_ty iter)
{
    
    void *data = NULL;

    bst_iter_ty iter_prev = {NULL};

    
    assert(bst);
    assert(BSTIsEmpty(bst) == 0);

    data = iter.iter_node->data;

    --bst->size;

    if(IsIterALeaf(iter))
    {
        if(IterSideChild(iter) == 0) 
        {
            iter.iter_node->parent->right = NULL;
        }

        else
        {
            iter.iter_node->parent->left = NULL;
        }

        free(iter.iter_node);
        iter.iter_node = NULL;
                
        return data; 

    }

    if (IsOnlyOneChild(iter))
    {
        bst_iter_ty temp;

        if(iter.iter_node->left)
        {     
            temp.iter_node = iter.iter_node->left;
        }

        else
        {
            temp.iter_node = iter.iter_node->right;
        }

        CopyIter(iter, temp);
        free(temp.iter_node);
        return data;
    }

    iter_prev = BSTPrev(iter);

    iter.iter_node->data = iter_prev.iter_node->data;

    if(IsIterALeaf(iter_prev))
    {
        iter_prev.iter_node->parent->left = NULL;
        free(iter_prev.iter_node);
        return data;
    }

   
    iter_prev.iter_node->left->parent = iter_prev.iter_node->parent;
      
    if(IterSideChild(iter_prev)== 1)
    {
        iter_prev.iter_node->parent->left = iter_prev.iter_node->left;
    }

    else
    {
        iter_prev.iter_node->parent->right = iter_prev.iter_node->left;
    }

    free(iter_prev.iter_node);       
    return data;
}
        


/* returns leftest leaf */
bst_iter_ty BSTBegin(const bst_ty *bst)
{
    bst_iter_ty iter = {NULL};

    assert(bst);

    iter.iter_node = bst->root;

    while (iter.iter_node->left)
    {
        iter.iter_node = iter.iter_node->left;
    }

    return iter;
}

/* refer to the position after the last element (righ-most element)  */
bst_iter_ty BSTEnd(const bst_ty *bst)
{
    bst_iter_ty iter = {NULL};

    assert(bst);

    iter.iter_node = bst->root;

    while (iter.iter_node->right != NULL)
    {
        iter.iter_node = iter.iter_node->right;
    }

    return iter;
}

/* returns iter to previous element */
bst_iter_ty BSTPrev(bst_iter_ty iter)
{
  
    
    if (iter.iter_node->left)
    {
        iter.iter_node = iter.iter_node->left;

        while (iter.iter_node->right)
        {
            iter.iter_node = iter.iter_node->right;
        }

        return iter;
    }

    else
    {
        while (iter.iter_node->parent->left == iter.iter_node)
        {
            iter.iter_node = iter.iter_node->parent;
        }
        iter.iter_node = iter.iter_node->parent;
        return iter;
    }


}

/* returns iter to next element  */
bst_iter_ty BSTNext(bst_iter_ty iter)
{
    if (iter.iter_node->right)
    {
        iter.iter_node = iter.iter_node->right;

        while (iter.iter_node->left)
        {
            
            iter.iter_node = iter.iter_node->left;
        }

        return iter;
    }

    while (iter.iter_node->parent->right == iter.iter_node)
    {
       iter.iter_node = iter.iter_node->parent;

    }

    iter.iter_node = iter.iter_node->parent;

    return iter;
    


}

/* the function checks if the 2 iterators are equal.
return 1 if equal 0 for not */
int BSTIter_Is_Equal(bst_iter_ty iter1, bst_iter_ty iter2)
{
    return (iter1.iter_node->data == iter2.iter_node->data);
}

/*the function gets iter and returns the dara at the location */
void *BSTGet_Data(const bst_iter_ty iter)
{

    return iter.iter_node->data;

}

/* Find data in BST according to the compare function.*/
bst_iter_ty BSTFind(const bst_ty *bst, void *what_to_find)
{

	bst_iter_ty iter = {NULL};
	iter.iter_node = bst->root;

	assert(bst);
	assert(what_to_find);

	if (BSTIsEmpty(bst))
	{
		return iter;
	}

    
	while (iter.iter_node)
	{
	 	if (bst->cmp(what_to_find, iter.iter_node->data) == 1)
		{
			iter.iter_node = iter.iter_node->right;
        }

        else if (bst->cmp(what_to_find, iter.iter_node->data) == -1)
		{

			iter.iter_node = iter.iter_node->left;
        }

		else
        {
		    return iter;
        }

    }

	iter.iter_node = NULL;
    return iter;
}




int BSTForeach(const bst_iter_ty from, const bst_iter_ty to, int (*action)(void *data, const void *param), const void *param)
{

	int res = 0;
	bst_iter_ty iter = from;

    assert(from.iter_node);
    assert(to.iter_node);
    assert(action);

	while (!BSTIter_Is_Equal(iter,to) && res == 0)
	{
		res = action(BSTGet_Data(iter), param);

		iter = BSTNext(iter);
	}
	return res;

}

static int IsIterALeaf(bst_iter_ty iter)
{
    return (iter.iter_node->right == NULL && iter.iter_node->left == NULL);
}

static int IsIterHasTwoChildren(bst_iter_ty iter)
{
    return (iter.iter_node->right != NULL && iter.iter_node->left != NULL);
}


static int IsOnlyOneChild(bst_iter_ty iter)
{
    return IsIterALeaf(iter) == 1 ? 0 : IsIterHasTwoChildren(iter) == 1 ? 0 : 1;
}


/* return 0 - right, return 1 - left */ 
static int IterSideChild(bst_iter_ty iter)
{
    return iter.iter_node->parent->right == iter.iter_node ? 0 : 1;
}


static void CopyIter(bst_iter_ty dest, bst_iter_ty src)
{
    dest.iter_node->data = src.iter_node->data;
    dest.iter_node->right = src.iter_node->right;
    dest.iter_node->left = src.iter_node->left;

    if(src.iter_node->right)
    {
        src.iter_node->right->parent = dest.iter_node;
    }

    if(src.iter_node->left)
    {
        src.iter_node->left->parent = dest.iter_node;
    }
   
}
