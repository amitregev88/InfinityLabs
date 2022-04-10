/**************************************
*Author: Amit Regev
*Reviewer: Noam Dan Hadad 
*Description:  implementation memset
*Infinity Labs OL124	
***********************************************************/

#include<stdio.h>
#include<stdlib.h> /*malloc*/
#include <string.h> /*strlen, strcat*/


typedef struct element{
	
	void *data;
	void (*Print)(void* data);
	void (*Add)(void* data, int additional);
	void (*Cleanup)(struct element *arr);
	
}element;


void setInt(struct element *e, int * val); /* function is checks the type of the variable */
void setData(struct element *e, void *, char);
void setFloat(struct element *e, float * val);
void setChar(struct element *e, char * val);

void PrintInt(void * );
void PrintChar(void * val);
void PrintFloat(void * val);

void AddToInt (void* val, int additional);
void AddToFloat (void* val, int additional);
void AddToString (void* val, int additional);

void Cleanup (struct element *arr);

int main()
{
	
	element arr[3];
	int integer = 30;
	float f = 3.14;
	char* c = (char*) malloc(20);
	printf("enter a string:\n");	
	scanf("%s", c); 

	

	
	setData(arr, &integer, 'i');
	setData(arr+1, &f, 'f');
	setData(arr+2, c, 'c');
	
	printf("arr before adding an integer:\n");
	arr[0].Print(arr[0].data);
	arr[1].Print(arr[1].data);
	arr[2].Print(arr[2].data);
	

	
	
	arr[0].Add(arr[0].data, 10);
	arr[1].Add(arr[1].data, 10);
	arr[2].Add(arr[2].data, 10);
	
	
	printf("\narr after adding an integer:\n");
	arr[0].Print(arr[0].data);
	arr[1].Print(arr[1].data);
	arr[2].Print(arr[2].data);
		

	arr[0].Cleanup(arr+0);
	arr[1].Cleanup(arr+1);
	arr[2].Cleanup(arr+2);
	

	printf("\narr after cleanup:\n");
	arr[0].Print(arr[0].data);
	arr[1].Print(arr[1].data);
	arr[2].Print(arr[2].data);
		
	
		
	free(c);

	return 0;
}


void setData(struct element *e, void *ptr, char type)
{
	switch(type)
	{
		case 'i':	setInt(e,(int*)ptr);
					break;
					
		case 'c':	setChar(e,(char*)ptr);
					break;
		
		case 'f':	setFloat(e,(float*)ptr);
					break;
		
		default:	break;
	}
}


void setInt(struct element *e, int * val) /*val is ptr after cast)*/
{
	e->data = val;
	e->Print = &PrintInt;
	e->Add = &AddToInt;
	e->Cleanup = &Cleanup;
}


void setFloat(struct element *e, float * val)
{
	e->data = val;
	e->Print = &PrintFloat;
	e->Add = &AddToFloat;
	e->Cleanup = &Cleanup;
}

void setChar(struct element *e, char * val)
{
	e->data = val;
	e->Print = &PrintChar;
	e->Add = &AddToString;
	e->Cleanup = &Cleanup;
}


void PrintInt(void* val)
{
	printf("%d ", *(int*)val);
}

void PrintFloat(void* val)
{
	printf("%f ", *(float*)val);
}

void PrintChar(void* val)
{
	printf("%s ", (char*)val);
}

void AddToInt (void* val, int additional)
{
	*(int*)val +=  additional;
	
}

void AddToFloat (void* val, int additional)
{
	*(float*)val +=  additional;
}

void AddToString (void* val, int additional)
{
	char* num = malloc(11); 
	char* tmp = (char*)malloc(strlen((char*)val)+11);
	
	/*char* num = malloc(log10(additional) + 2); */
	/*char* tmp = (char*)malloc(strlen((char)arr.val) + log10(additional) + 2);*/
	
	if ((tmp == NULL) || (num == NULL))
		
		exit(1);
	
	sprintf(num, "%d", additional);
	strcat((char *)val, num);
	
	free(num);
	free(tmp);
	
}

void Cleanup (struct element *arr)
{
	
	arr->data = NULL;
	arr->Print = NULL;
	arr->Add = NULL;
	
}
	
	

	

