#include <stdio.h>
#include <stdlib.h>

/*int *update_arr(int *arr, size_t len);*/
void josephus(int *arr, size_t n, size_t k);

int main()
{
	size_t n = 143;  /* number of soliders*/
	size_t k = 3; /*solider No. that will be killed first*/ 
	size_t i = 0;
	/*
	printf("Enter the number of soldiers (mimimun 2 soldiers)\n");
	scanf("%lu", &n);
	printf("choose a soldier No. to die first\n");
	scanf("%lu", &k);
	*/
	
	int *arr = (int*)malloc(n*sizeof(int));

	
	if(arr == NULL)
	{
		 printf("Memory error allocation\n");
		 return 1;
	}		 
		 
	for(; i < n; i++) *(arr + i) = i + 1; /* initialize arr from 1 until n */

	josephus(arr, n, k);
	free(arr);
	arr = NULL;
	return 0;
}


void josephus(int *arr, size_t n, size_t k)
{
	
	size_t i = 0;
	size_t j = 0;
	
	while(n!=1)
	{
		i = (i + k - 1)%n; /* this expression calculates the next soldier will die */
		n--;
		if (*(arr + i) != 0)  
		{
			*(arr + i) = 0;  /*value arr[i] = 0 means - solider die */
			for(j = i;j < n; j++) /*update the arr*/
				{
				  arr[j] = arr[j + 1];
				}
			arr[n] = (int) NULL;
		}
	}
	
	printf("Soldier No. %d survived\n", *arr);

}

/*

#include <stdio.h>

int find_next_allive (int *arr, int size, int killer);

int main()
{
    int size = 100;
    int i = 0;
    int arr[100];
    int killer = 0;
    int next_killer = 2;
    int next_to_kill = 1;
    int survivour = -1;

    for (i = 0; i < size; ++i)
        *(arr + i) = 1;

    while (survivour == -1)
    {

        /** finds the next_to_kill and check if it's **
        ** a KILLER himself if not KILL him         **/
/*
        next_to_kill = find_next_allive(arr, size, killer);

        if (next_to_kill != killer)
        {
            arr[next_to_kill] = 0;
        }
        else
        {
            survivour = killer;
            break;
        }

        next_killer = find_next_allive(arr, size, killer);

        if (next_killer != killer)
        {
            killer = next_killer;
        }
        else
        {
            survivour = killer;
            break;
        }
    }

    ++survivour;

    printf ("The Survivour is # %d\n", survivour);

    return 0;
}
*/
/* Find next Alive to Kill him, if next one is the Killer return -1
else return index of the next one need to kill**/

/*int find_next_allive (int *arr, int size, int killer)
{

    int index = killer + 1; 
    if (index + 1 > size)
    {
        index = 0;
    }

    while (arr[index] != 1)
    {
        if (index == killer)
        {
            return killer ;
        }
        else
        {
            ++index;
        }

        if (index + 1 > size)
        {
            index = 0;
        }
    }

    return index;
}
*/

