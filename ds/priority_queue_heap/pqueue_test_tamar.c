/*************************************************************
*OL124 Priority Queue project
*pqueue.h
*pqueue.c
* pqueue_test.c
* *
*ver 1.0
******************************************************************/
#include <stdio.h>
#include"pqueue.h"

#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  (x)==(y)? IF_SUCCESS(1) : IF_SUCCESS(0)

void PrintIntData(void *data);
void PrintCharData(void *data);
void PrintFloatData(void *data);
void PrintStringData(void *data);
void PrintSize_tData(size_t data);
void PrintVoidData(void *data);
void PrintPQList(pqueue_ty *pQ);
int ComparePriority(const void * priority1, const void * priority2);
int FindData(const void * list_data, const void * to_find);

pqueue_ty * Test_PQCreate(void);
void Test_PQEnQueue(pqueue_ty * pQ, void *data, size_t expected_size);
void Test_PQDeQueue(pqueue_ty * pQ, size_t expected_size, int expected_priority);
void Test_PQPeek(pqueue_ty * pQ, char * expected_str, int expected_priority);
void Test_PQIsEmpty(pqueue_ty * pQ, int expected_result);
void Test_PQSize(pqueue_ty * pQ, size_t expected_size);
void Test_PQErase(pqueue_ty * pQ, char * expected_str, size_t expected_size);


typedef struct statment
{
	char str[10];
	int priority;
}Statment;



int main()
{
	
	Statment str1 = {"things", 3};
	Statment str2 = {"is Sweet", 2};
	Statment str3 = {"in all", 4};
	Statment str4 = {"!!!\n", 1};
	Statment str5 = {"Change", 5};
		
	pqueue_ty * pQ = Test_PQCreate();
	
	Test_PQIsEmpty(pQ, 1); /*empty*/
	Test_PQSize(pQ, 0);
	
	
	Test_PQEnQueue(pQ, &str1, 1);
	Test_PQEnQueue(pQ, &str2, 2);
	Test_PQEnQueue(pQ, &str3, 3);
	
	Test_PQSize(pQ, 3);	
	
	Test_PQEnQueue(pQ, &str4, 4);
	Test_PQEnQueue(pQ, &str5, 5);
	
	
	Test_PQIsEmpty(pQ, 0); /*not empty*/
	
	Test_PQPeek(pQ, str5.str, str5.priority);
	
	Test_PQSize(pQ, 5);
		
	Test_PQErase(pQ, str1.str, 4);
	
	Test_PQDeQueue(pQ, 3, 5);

	Test_PQDeQueue(pQ, 2, 4);
	Test_PQDeQueue(pQ, 1, 2);
	
	Test_PQDeQueue(pQ, 0, 1);
	

	PQDestroy(pQ);

	return 0;
}


/******************************************************************
*
*					Test Functions
*
******************************************************************/

pqueue_ty * Test_PQCreate(void)
{
	pqueue_ty *pQ = PQCreate(&ComparePriority);
	
	if(pQ)
	{
		printf("Success : PQCreate() ");
		PrintVoidData((void*)pQ);
		return pQ;
	}

	printf("Faile : PQCreate() ");
	PrintVoidData((void*)pQ);
	
	return NULL;
}


/******************************************************************/

void Test_PQEnQueue(pqueue_ty * pQ, void *data, size_t expected_size)
{
	PQEnQueue(pQ, data);
	
	if(PQSize(pQ) == expected_size)
	{
		printf("Success : PQEnQueue() \n");
	}
	else
	{
		printf("Failed : PQEnQueue() \n");
	}

}

/******************************************************************/

void Test_PQDeQueue(pqueue_ty * pQ, size_t expected_size, int expected_priority)
{
	void * data = PQDeQueue(pQ);
	
	if(PQSize(pQ) == expected_size && ((Statment *)data)->priority == expected_priority)
	{
		printf("Success : PQDeQueue() \n");
	}
	else
	{
		printf("Failed : PQDeQueue() \n");
	}

}

/******************************************************************/

void Test_PQPeek(pqueue_ty * pQ, char * expected_str, int expected_priority)
{
	void * data = (void *)PQPeek(pQ);
	
	if(((Statment *)data)->str == expected_str && ((Statment *)data)->priority == expected_priority)
	{
		printf("Success : PQPeek() \n");
	}
	else
	{
		printf("Failed : PQPeek() \n");
	}

}


/******************************************************************/

void Test_PQIsEmpty(pqueue_ty * pQ, int expected_result)
{
	if(PQIsEmpty(pQ) == expected_result)
	{
		printf("Success : PQIsEmpty() \n");	
	}
	else
	{
		printf("Failed : PQIsEmpty() \n");
	}

}

/******************************************************************/

void Test_PQSize(pqueue_ty * pQ, size_t expected_size)
{
	
	if(PQSize(pQ) == expected_size)
	{
		printf("Success : PQSize() \n");
	}
	else
	{
		printf("Failed : PQSize() \n");
	}
}


/******************************************************************/

void Test_PQErase(pqueue_ty * pQ, char * expected_str, size_t expected_size)
{
	void * data = PQErase(pQ, &FindData, expected_str);
	
	if(((Statment *)data)->str == expected_str && PQSize(pQ) == expected_size)
	{
		printf("Success : PQErase() \n");
	}
	else
	{
		printf("Failed : PQErase() \n");
	}

}


/******************************************************************
*
*			Additional Functions
*
******************************************************************/


int ComparePriority(const void * data1, const void * data2)
{
	return ((Statment*)data1)->priority - ((Statment*)data2)->priority;

}

/******************************************************************/

/* Find (*is_match) function */
int FindData(const void * list_data, const void * to_find)
{
	if((char*)list_data == (char*)to_find)
	{
		/* strcmp((char*)list_data, (char*)to_find) */
		return 1;
	}
	
	return 0; 
}


/******************************************************************/

void PrintPQList(pqueue_ty *pQ)
{
	size_t len = PQSize(pQ);
	void * data = NULL;
	
	if(!len)
	{
		printf("List is Empty!\n");
	}
	
	for( data = (void*)PQPeek(pQ) ; len > 0 ; len--, data = (void*)PQPeek(pQ))
	{	
		printf("%s ", ((Statment *)data)->str);
		PQDeQueue(pQ);
	}	
}




/******************************************************************/

void PrintIntData(void *data)
{
	printf(" %d\n", *(int*)data);
}
/******************************************************************/
void PrintCharData(void *data)
{
	printf(" %c\n", *(char*)data);
}
/******************************************************************/

void PrintFloatData(void *data)
{
	printf(" %f\n", *(float*)data);
}
/******************************************************************/

void PrintStringData(void *data)
{
	printf(" %s\n", (char*)data);
}
/******************************************************************/

void PrintSize_tData(size_t data)
{
	printf(" %lu\n", data);
}

/******************************************************************/
void PrintVoidData(void *data)
{
	printf(" %p\n", data);
}
/******************************************************************/

