#include <stdio.h> /* printf */
#include "slinked_list.h"
#include "queue.h"


#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  (x)==(y)? IF_SUCCESS(1) : IF_SUCCESS(0)


void Test(void);

int main(void)
{
	Test();
	
	return 0;
}





void Test(void)
{
	int num1 = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5, num6 = 6;
	
	queue_ty *queue1 = NULL;
	
	queue_ty *queue2 = NULL;
	
	
	
	printf("Testing of QCreate() function:\n");
	
	queue1 = QCreate();
	
	if (queue1)
	{
		printf("Testing of QCreate() function succeeded\n");
	} 
	
	else
	{
		printf("Testing of  QCreate() function failed\n");
	}
	

	
	printf("\nTesting of  QIsEmpty() function in case queue is empty:\n");
	TEST(QIsEmpty(queue1), 1);
	
	printf("\nTesting of QSize() function in case queue is empty:\n");
	TEST(QSize(queue1), 0);
	
	
	printf("\nTesting of  QPeek() function in case queue is empty:\n");
	TEST(QPeek(queue1), NULL);
	
	printf("\nTesting of QDeQueue() function  in case queue is empty:\n");
	
	
	TEST((QEnQueue(queue1, &num1)), 0);
	
	
	printf("\nTesting of QEnQueue() and  QPeek function  in case queue is not empty:\n");
	
	TEST(QEnQueue(queue1, &num1), 0);
	TEST(QEnQueue(queue1, &num2), 0);
	TEST(QEnQueue(queue1, &num3), 0);
	
	TEST(QPeek(queue1), &num3); /*?*/
	
	printf("\nTesting of QSize() function in case queue is not empty:\n");
	TEST(QSize(queue1), 3); /*?*/
	
	
	
	printf("\nTesting of QDeQueue() function  in case queue is not empty:\n");
	
	TEST(QDeQueue(queue1), &num1);
	
	printf("\nTesting of QSize() function in case queue is not empty:\n");
	TEST(QSize(queue1), 2); /*?*/
	
	queue2 = QCreate();
	
	if (queue2)
	{
		printf("\nTesting of QCreate() function succeeded\n");
	} 
	
	else
	{
		printf("Testing of  QCreate() function failed\n");
	}
	
	
	
	printf ("\nTesting of QAppend function :\n");
	
	TEST(QEnQueue(queue2, &num4), 0);
	TEST(QEnQueue(queue2, &num5), 0);
	TEST(QEnQueue(queue2, &num6), 0);
		

	QAppend(queue1, queue2);	
	

	
	
	TEST(QSize(queue1), 5);	/*?*/
	
	TEST(QIsEmpty(queue2), 1);
	
	TEST(QPeek(queue1), &num6); /*?*/
	

	QDestroy(queue1);	
	QDestroy(queue2);	
	



}

