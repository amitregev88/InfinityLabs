/*************************************************************
* Author: Amit Regev
* Reviewer: Yotam Aharon
* Date: 27/6/22 
* OL124 Implementation of AVL tree recursive
*******************************************************************/
#include <assert.h> /*assert*/
#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc */ 
#include "avl.h"

typedef struct avl_node node_ty;

static size_t IS_SAME_KEY = 0;

struct avl_node
{
    void *key;
    void *data;
    node_ty *right;
    node_ty *left;
};

struct avl
{
    node_ty *root;
    compare_ty cmp;
};

static size_t AVLSizeRec(node_ty *root);
static void InOrder(node_ty *node, int (*action)(void *val, const void *param),const void *param);
static void PostOrder(node_ty *node, int (*action)(void *val, const void *param),const void *param);
static void PreOrder(node_ty *node, int (*action)(void *val, const void *param),const void *param);
static node_ty *AVLFindRec(const avl_ty *avl, node_ty *iter ,void *key);
static node_ty *AVLInsertRec(avl_ty *avl, node_ty *relative_root, node_ty *new_node);
static node_ty *LeftRotate(node_ty *node);
static node_ty *RightRotate(node_ty *node);
static int AVLHeightRec(const node_ty *node);
static int GetMaxVal(int val1, int val2);
static int GetBalanceFactor(node_ty *node);
static void AVLDestroyRec(node_ty *node);
static node_ty *GetPrevNode(node_ty *node);
static node_ty *AVLRemoveRec(avl_ty *avl, node_ty *root, void *key, void **_data);
static void SwapNode(node_ty *node1, node_ty *node2);

/*Function creates a new binary tree data structure
return NULL if malloc fails */
avl_ty *AVLCreate(compare_ty compare)
{  
    avl_ty *avl_tree = (avl_ty *) malloc (sizeof(avl_ty));
    if(!avl_tree)
    {
        return NULL;
    }

    assert(compare);

    avl_tree->cmp = compare;
    avl_tree->root = NULL;

    return avl_tree; 
}

/*Function frees all the alements in the tree*/
void AVLDestroy(avl_ty* avl)
{
    assert(avl);
    
    if(AVLIsEmpty(avl) == 0 )
    {
        AVLDestroyRec(avl->root);
    }

    free(avl); 
}

/*Function returns the number of items stored in AVL*/
size_t AVLSize(const avl_ty *avl)
{
    assert(avl);
    return AVLSizeRec(avl->root);
}

/*Return 1 - is Empty, 0 - not Empty*/
int AVLIsEmpty(const avl_ty *avl)
{
    assert(avl);
    return (avl->root == NULL);
}

/*Success return 0 */
int AVLInsert(avl_ty *avl, void *key, void *val)
{
    node_ty *to_insert = NULL;

    to_insert = (node_ty *)malloc(sizeof(node_ty));  
    if(NULL == to_insert)
    {
        return 1;
    }

    assert(avl);
    assert(key);
    assert(val);

    to_insert->key = key;
    to_insert->data = val;
    to_insert->left = NULL;
    to_insert->right = NULL;

    if(avl->root == NULL)
    {
        avl->root = to_insert;
        return 0;
    }

    avl->root =  AVLInsertRec(avl, avl->root, to_insert);

    if (IS_SAME_KEY != 0)
    {
        IS_SAME_KEY = 0;
        free(to_insert);
        return 2;
    } 

    else 
    {
        return IS_SAME_KEY;
    }
}

/*Removes node. returns pointer to node to remove */
void* AVLRemove(avl_ty *avl , void *key)
{
    void *data = NULL;
    
    assert(avl);
    assert(key);
    
    AVLRemoveRec(avl,avl->root,key,&data);

    return data;
}

/*Find data in AVL according to the compare function.*/
void* AVLFind(const avl_ty *avl, void *key)
{
	node_ty *find_res = NULL;

	assert(avl);
	assert(key);

	if (AVLIsEmpty(avl))
	{
		return NULL;
	}

    find_res = AVLFindRec(avl,avl->root,key);

    if (find_res)
    {
        return find_res->data;
    }

    else
    {
        return NULL;
    }
	
}

/*Return height 0 - 64  */
int AVLHeight(const avl_ty *avl)
{
    assert(NULL != avl);

    return AVLHeightRec(avl->root);
}

/*Success return 0 */
int AVLForeach(avl_ty *avl, int (*action)(void *val, const void *param), const void *param, order_ty order_of_action)
{

    assert(avl);
    assert(action);

    switch (order_of_action)
    {
    case pre_order:
        PreOrder(avl->root,action,param);
        break;

    case in_order:
        InOrder(avl->root,action,param);
        break;

    case post_order:
        PostOrder(avl->root,action,param);
        break;        
    
    default:
        return 1;

    }

    return 0;
}

static int GetBalanceFactor(node_ty *node) 
{
    if (NULL == node)
    {
        return -1;
    }

    return (AVLHeightRec(node->left) - AVLHeightRec(node->right));
}

static int AVLHeightRec(const node_ty *node) 
{     
    if (NULL == node)
    {
        return -1;
    }

    return (1 + GetMaxVal(AVLHeightRec(node->left), AVLHeightRec(node->right)));    
}

static int GetMaxVal(int val1, int val2)
{
    return val1 > val2 ? val1: val2;
}

static node_ty *RightRotate(node_ty *node) /* for left-left */
{
    node_ty *nleft = node->left;

    node_ty *right_nleft = nleft->right;

    nleft->right = node;

    node->left = right_nleft;

    return nleft;
}

static node_ty *LeftRotate(node_ty *node) /* for right-right */
{
    node_ty *nright = node->right;

    node_ty *left_nleft = nright->left;

    nright->left = node;

    node->right = left_nleft;

    return nright;
}

static node_ty *AVLInsertRec(avl_ty *avl, node_ty *root, node_ty *new_node)
{

    int bf = 0; /* balance factor */
            
    if(root == NULL)
    {
        root = new_node;
        return root;
    }

    if (avl->cmp(root->key,new_node->key) == 1)
    {
        root->left = AVLInsertRec(avl,root->left,new_node);

    }

    else if (avl->cmp(root->key,new_node->key) == -1)
    {
        root->right = AVLInsertRec(avl,root->right,new_node);
    }

    if (avl->cmp(new_node->key, root->key) == 0)
    {
        
        IS_SAME_KEY = 1;
        return root;
    }

    /*balance tree*/
    
    bf = GetBalanceFactor(root);
    
    if (bf > 1 && avl->cmp(root->left->key,new_node->key)) /*left - left */ 
    {
            return RightRotate(root);
    }

    if (bf < -1 && avl->cmp(new_node->key, root->right->key)) /*right - right*/
    {
         return LeftRotate(root);
    }

    if (bf > 1 && avl->cmp(new_node->key, root->right->key)) /*left - right */ 
    {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    if (bf < -1 && avl->cmp(root->right->key,new_node->key)) /*right - right*/
    {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root;
}

static node_ty *AVLFindRec(const avl_ty *avl, node_ty *iter ,void *key)
{
    node_ty *iter_node = NULL;

	if(!iter)
    {
        iter_node = NULL;
    }
    
    else if (avl->cmp(iter->key, key) == 1)
	{
		iter_node = AVLFindRec(avl, iter->left,key);
    }

    else if (avl->cmp(iter->key, key) == -1)
	{
		iter_node = AVLFindRec(avl, iter->right,key);
    }

	else
    {
		iter_node = iter;
    }

    return iter_node;
}

static void PreOrder(node_ty *node, int (*action)(void *val, const void *param),const void *param)
{
    if(!node)
    {
        return;
    }

    action(node->data, param);
    
    PreOrder(node->left, action,param);

    PreOrder(node->right, action,param);
}

static void PostOrder(node_ty *node, int (*action)(void *val, const void *param),const void *param)
{

    if(!node)
    {
        return;
    }

    PostOrder(node->left, action,param);

    PostOrder(node->right, action,param);
    
    action(node->data, param);
    
}

static void InOrder(node_ty *node, int (*action)(void *val, const void *param),const void *param)
{

    if(!node)
    {
        return;
    }

    InOrder(node->left, action,param);

    action(node->data, param);
    
    InOrder(node->right, action,param);
}

static size_t AVLSizeRec(node_ty *root)
{
    if (!root)
    {
        return 0;
    }

    return 1 + AVLSizeRec(root->left) + AVLSizeRec(root->right);    
}

static void AVLDestroyRec(node_ty *node)
{
    if(!node)
    {
        return;
    }

    if(!node->left && !node->right)
    {
        free(node);
        node = NULL;
        return;
    }

    AVLDestroyRec(node->left);
    node->left = NULL;
    AVLDestroyRec(node->right);
    node->right = NULL;

    AVLDestroyRec(node);
}

static node_ty *AVLRemoveRec(avl_ty *avl, node_ty *root, void *key, void **_data)
{ 

    int bf = 0; /*balance factor */ 
    
    if (!root)
    {
        return root;
    }
    
    switch (avl->cmp(root->key,key))
    {
    case 1:
        root->left = AVLRemoveRec(avl, root->left, key,_data);
        break;
    
    case -1:
        root->right = AVLRemoveRec(avl, root->right, key,_data);
        break;

    case 0:
  
        *_data = root->data;
        
        if(!root->left && !root->right)  /* in case node is a leaf */ 
        {
             
            free(root);
            return NULL;
        }

        else if (!root->left && root->right) /* in case node has only right child */ 
        {
            node_ty *tmp = NULL;
            tmp = root->right;
            free(root);
            return tmp;
        }

        else if (root->left && !root->right) /* in case node has only left child */ 
        {
            node_ty *tmp = NULL;
            tmp = root->left;
            free(root);
            return tmp;
        }

        else /* in case node has two children */
        {
            node_ty *tmp = NULL;
            tmp = GetPrevNode(root); 
            SwapNode(tmp,root);
            root->left = AVLRemoveRec(avl, root->left, tmp->key,_data);
        }

    break;

    default:
        break;
    }

    bf = GetBalanceFactor(root);

    if(bf > 1 && GetBalanceFactor(root->left) >= 0) /* left - left */ 
    {
        return RightRotate(root);
    }

    else if (bf > 1 && GetBalanceFactor(root->left) < 0)  /* left - right */ 
    {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    else if (bf < -1 && GetBalanceFactor(root->right) <= 0)  /* right - right */ 
    {
        return LeftRotate(root);
    }

    else if (bf < -1 && GetBalanceFactor(root->right) > 0)  /* right - left */ 
    {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    } 

    return root; 
}   
          
static node_ty *GetPrevNode(node_ty *node)
{
    node_ty *iter = node;

    assert(node);

    iter = node->left;


    while(iter->right)
    {
        iter = iter->right;
    }

    return iter;   
}

static void SwapNode(node_ty *node1, node_ty *node2)
{
    void *key = NULL;

    void *data = NULL;

    key = node1->key;

    data = node1->data;

    node1->key = node2->key;

    node1->data = node2->data;

    node2->key = key;

    node2->data = data;
} 