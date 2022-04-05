#include <stdio.h>

typedef struct
{
	int imax;
	int imin;
	int profit;
}bursa; 

bursa FuncMaxProfit (int arr[], size_t size);

int main()
{
	
	int arr[] = {6,12,3,5,1,4,9,2};
	bursa a = FuncMaxProfit(arr,8);
	
	printf("The biggest profit is: %d. buy index is: %d. sell index is: %d\n", a.profit, a.imin, a.imax);  

	return 0;
}


bursa FuncMaxProfit (int arr[], size_t size)
{

bursa stock = {0,0,0};

size_t itmp= 0, i = 0;

	for (i = 1;i < size;i++)
	{
		if (arr[i] > arr[stock.imax])
		{
			stock.imax = i;
			stock.profit = arr[stock.imax] - arr[stock.imin];
		}
	
		else if (arr[i] < arr[itmp])
		{	 
			itmp = i;
		}
	
		if (arr[i]- arr[itmp] > stock.profit)
		{
			stock.profit = arr[i] - arr[itmp];
			stock.imin = itmp;
			stock.imax = i;
		}
	}
	
	return stock;
}

		 	
