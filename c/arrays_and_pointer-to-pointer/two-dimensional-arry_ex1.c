/**********************************
*Amit Regev
*
*
******************************************/



#include<stdio.h>
void printmatrix (int arr[][3]);
/*
void printmatrix2 (int arr1[], int arr2[])
{	

	int i = 0, j = 0;
	printf("\n\n\n");
	printf("The matrix:\n");
	
	for (i = 0; i < 3; i++)
	{
		printf("%d",arr1[i]);
	
		for (j = 0; j < 3; j++)
		{
			printf("%d",arr2[j]);
		}
	printf("\n");
	}
}	

int main ()
{
	
	int row[3] = {1,4,6};
	int column[3] = {2,3,5};
	
		
		printf("The matrix:\n");
		printmatrix2(row, column);

	
	
	
	return 0;	
}

*/



int main ()
{
	int i = 0, j = 0;
	int arr[3][3];
	printf("enter values to the matrix\n");
	for (i = 0; i < 3; i++)
	{
		printf("Line %d:\n", i + 1);
		for (j = 0; j < 3; j++)
		{
			scanf("%d",&arr[i][j]);
		}
	}
		printf("%lu",sizeof(arr[3][1]));
	/*printmatrix(row, colum);*/
	return 0;		
	
	
}



void printmatrix (int arr[][3])
{
	int i = 0, j = 0;
	printf("\n\n\n");
	printf("The matrix:\n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("%d",arr[i][j]);
		}
	printf("\n");
	}
}
	




