/*************************************************************
*OL124  Test HashTable project
*
*   Test
******************************************************************/

#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,a,y)  if ((x) a (y)) {IF_SUCCESS(1);}else{IF_SUCCESS(0);}

#include <stdio.h> /* printf */
#include <string.h> /*strcmp*/
#include <stdlib.h> /*malloc*/
#include "hashtable.h"

typedef struct 
{
	int id; /*key*/
	char name[20]; /*value*/

}ht_person_ty;



int IsMatch(const void* data1, const void* data2)
{
    const ht_person_ty *p1 = data1;
    const ht_person_ty *p2 = data2;

    if(p1->id == p2->id)
    {
        return 1;
    }
    return 0;  
}

int IsSameStr(const void *data1, const void *data2)
{
	const char *str1 = data1;
	const char *str2 = data2;

	return (strcmp(str1, str2) == 0);
}

int HT_Func(const void *data)
{

	return ((*(int *)data + 38) % 20);

}

int HT_Str_Func(const void *data)
{
	const char *str = data;
	int hash = 5381;
	int c = 0;

    while ((c = *str++))
	{
		hash += c;
	}
        
	return (hash % 400);
}

static int PrintPerson(void *val, const void *param)
{
    ht_person_ty* temp = NULL;
	temp = (ht_person_ty *)val;
    
    printf("ID: %d , NAME: %s\n",temp->id ,temp->name);
    param = param;
    return 0;
}

void HT_Test(void)
{
	ht_ty *ht = NULL;

	ht_person_ty arr[20] = {{1,"Amit"}, {2,"Amir"}, {3,"David"}, {4,"Alex"}, {5,"Noya"}, {6,"Liat"}, {7,"Ron"}, {8,"Shir"}, {9,"Dan"}, {10,"Amit"}, {11,"Dana"}, {12,"Merav"}, {13,"Yoni"}, {14,"Mani"}, {15,"Pie"}, {16,"Eli"}, {17,"Naama"}, {18,"Dany"}, {19,"Benny"}, {20,"Itay"}};

	printf("*****************  Hash Table Test  **************\n");
	
	printf("\n\nTesting of HTCreate function:\n");

	ht = HTCreate(&IsMatch,&HT_Func ,20);

	TEST(ht, != , NULL);

	printf("\nTesting of Size and IsEmpty function:\n");

	TEST(HTIsEmpty(ht), == , 1);
	TEST(HTSize(ht), ==, 0);

	printf("\nTesting of Insert function:\n");

	HTInsert(ht, &arr[0]);
	HTInsert(ht, &arr[1]);
	TEST(HTInsert(ht, &arr[2]), == , 0);
	HTInsert(ht, &arr[3]);
	HTInsert(ht, &arr[4]);

	TEST(HTIsEmpty(ht), == , 0);
	TEST(HTSize(ht), ==, 5);	
	TEST(HTInsert(ht, &arr[2]), == , 1);
	TEST(HTSize(ht), ==, 5);

	printf("\nTesting of Remove function:\n");

	TEST(HTRemove(ht ,&arr[0]), == , &arr[0]);
	TEST(HTSize(ht), ==, 4);

	HTInsert(ht, &arr[5]);
	HTInsert(ht, &arr[6]);
	HTInsert(ht, &arr[7]);
	HTInsert(ht, &arr[8]);
	HTInsert(ht, &arr[9]);
	HTInsert(ht, &arr[10]);
	HTInsert(ht, &arr[11]);
	HTInsert(ht, &arr[12]);
	HTInsert(ht, &arr[13]);
	HTInsert(ht, &arr[14]);
	HTInsert(ht, &arr[15]);
	HTInsert(ht, &arr[16]);
	HTInsert(ht, &arr[17]);
	HTInsert(ht, &arr[18]);
	HTInsert(ht, &arr[19]);


	printf("\nTesting of Find function:\n");

	TEST(HTFind(ht,&arr[15]),==, &arr[15]);


	printf("\nTesting of ForEach function:\n");

	TEST(HTForeach(ht,PrintPerson,NULL),==,0);


	HTDestroy(ht);
}

void Dictionary_Test(void)
{
	ht_ty *ht = NULL;
	FILE * fp;
	char *str = NULL;
	char input_str[35] = {0};

	printf("*****************  Dictionary Test  **************\n");

	ht = HTCreate(&IsSameStr,&HT_Str_Func ,400);

   	if((fp = fopen("words.txt", "r")) == NULL)
   	{
	    printf("Error in opening file");
		return;
   	}
	str = malloc(35);
	fscanf(fp, "%s", str);
   	while(!feof(fp)) /*checks if end-of-file indicator*/
   	{
	 	HTInsert(ht, str);
		str = malloc(35);
		fscanf(fp, "%s", str);
	}
	free(str);
    fclose(fp);
   
   	printf("Please Enter a word to the spell checker:");
   	scanf("%s", input_str);
   	if (HTFind(ht,input_str))
   	{
	   printf("the word: %s was found in linux dictionary\n",input_str);
   	}
   	else
   	{
		printf("the word: %s is NOT in linux dictionary\n",input_str);
   	}
   	fflush(stdin);

	HTDestroyTotally(ht);
}

int main(void)
{
	HT_Test();

	Dictionary_Test();

	return 0;
}