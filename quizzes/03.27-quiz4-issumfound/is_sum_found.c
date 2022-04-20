/* ***********************************************************
*Author: Amit Regev
*Reviewer: 
*Description: the program checks if there two elements equal to sum in a given sorted array. 
*Quiz No.4 03.27.22
*************************************************************** */

#include <stdio.h> /* printf*/



typedef struct{
	int ileft;
	int iright;
	int value;
	}arrsum;
	
arrsum IsSumFound(int arr[], int sum);
	 
int main()
{
	int array[] = {2,5,9,12,16,24,32,45};
	int sum = 33;
	arrsum res;
	
	res = IsSumFound(array, sum);
	printf("index element 1:  %d index element 2:  %d result: %d\n", res.ileft, res.iright, res.value);
	
	return 0;
}
arrsum IsSumFound(int arr[], int sum)
{
	int i = 0, left = 0 , right = 0;
	
	arrsum sm;
	
	for (i = 0; i < 8; i++)
	{/*empty*/}
	
	right = i - 1;
	
	while(left < right)
	
	
	if (arr[left] + arr[right] < sum)
		left++;
	
	else if (arr[left] + arr[right] > sum)
		{
		right--;
		
		}
	else if (arr[left] + arr[right] == sum)
	{	
		sm.ileft = left;
		sm.iright = right;
		sm.value = 1;
		return sm;
	 }
	 
	sm.ileft = (int)NULL;
	sm.iright = (int)NULL;
	sm.value = 0;
	return sm;
	
	
} 
			
		
		
		
	
