/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 03.05.22
* OL124 Linked List Exercises
*************************************************************************************/

typedef struct node
{
	void *data;
	struct node *next;
}node_t;


/*Reverse the order of a given slist*/

node_t *Flip(node_t *head);

/*Tells wheter a given slist has loop */

int HasLOOP(const node_t *head);

/* Return a pointer to a first node mutual to both slists, if any. */

node_t *FindIntersection(node_t *head_1, node_t *head_2);


node_t *Flip(node_t *head)
{

	node_t curr = NULL; next_curr = NULL; tmp = NULL;
	
	if ((!head) || (!(head->next)))
	{
		return head;
	} 
	
	curr = head;
	
	curr->next = NULL;
	
	next_curr = head->next;
	
	tmp = next_curr->next;
	
	
	while (tmp->next != NULL)
	{
	
		next_curr->next = curr;
	
		curr = next_curr;
	
		next_curr = tmp; 
	
		tmp = tmp->next;
	}
		
	next_curr->next = curr;
	
	tmp->next = next_curr;
	
	return tmp; 
	
}
	
	
int HasLoop(const  node_t *head)
{
	node_t *has_loop = NULL;
	int flag = 0;
	
	has_loop = Flip(head);
	
	
	if (has_loop == head)
	{
		flag = 1;
	}
	
	Flip(head);
	
	return flag;
}


node_t FindIntersection(slist_node_ty *head_1, slist_node_ty *head_2)
{
	
	size_t i = 0; size_list1 = 0, size_list2 = 0, steps = 0;
	
	size_list1 = SListSize(head_1);
	
	size_list2 = SListSize(head_2);
	
	if (size_list1 < size_list2)
	{
		node_t tmp = NULL;
				
		tmp = head_1;
		
		head_1 = head_2;
		
		head_2 = tmp;
		
		steps = size_list2 - size_list1;
	}
	
	else
	{
		steps = size_list1 - size_list2;
	}
	
	
	for (; i <= steps; ++i)
	{
		head_1 = head_1->next;
	}
	

	while ((NULL != head_1) && (NULL != head_2))
	{
		if (head_1 == head_2)
		{
			return head_1;
		}
		
		head_1 = head_1->next;
		head_2 = head_2->next;
	}
	
	return NULL;
}





