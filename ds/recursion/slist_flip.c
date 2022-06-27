/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 22/6/22 
* OL124 Singly List Flip recursion
*******************************************************************/
#include <assert.h>

node_t *FlipList(node_t *node)
{

	node_t *current_next = NULL;
	
	assert(node);
	
	if (node->next == NULL)
	{
		return node;
	}

	current_next = FlipList(node->next);
	
	current_next->next = node;
	
	node->next = NULL;
	
	return node;
}

