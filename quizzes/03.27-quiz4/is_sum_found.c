/* ***********************************************************
*Author: Amit Regev
*Reviewer: 
*Description: the program checks if there two elements in sorted array given that equal to sum  
*Quiz No.4 03.27.22
*************************************************************** */

#include <stdio.h> /* printf*/

int IsSumFound(int arr[], int sum);

int main()
{
	int array[] = {2,5,9,12,16,24,32,45};
	int sum 33;
	res = 0;
	
	res = IsSumFound(array, sum);
	
	
	return 0;
}
int IsSumFound(int arr[], int sum)
{
	int i = 0, left = 0 , right = 0;
	for (i = 0; arr[i] != NULL; i++)
	{/*empty*/}
	
	right = i - 1;
	while(left < right)
	
		
	
	
	while(left < right)
	
	if (arr[right] > sum)
		right--;
		
	else if (arr[left] > sum)
		return 0;
		
	else if
		break;		
	
	if (arr[left] + arr[right] < sum)
		left++;
	
	else if (arr[left] + arr[right] > sum)
		{
		right--;
		left = 0;
		}
	else if (arr[left] + arr[right] == sum)
		printf ("sum is found. %d in 
		return 1;
		
		
		
	
