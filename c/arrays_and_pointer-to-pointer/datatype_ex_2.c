#include<stdio.h>
#include<stdlib.h>

int main()
{
	size_t datatype[11];
	size_t i = 0;
	
	char typename[11] = {"short int","unsigned short int","unsigned int","int", "long int","unsigned long int","signed char", "unsigned char", "float", "double", "long double"};
	
	datatype[0] = sizeof(short int);
	datatype[1] = sizeof(unsigned short int);
	datatype[2] = sizeof(unsigned int);
	datatype[3] = sizeof(int);
	datatype[4] = sizeof(long int );
	datatype[5] = sizeof(unsigned long int );
	datatype[6] = sizeof(signed char);
	datatype[7] = sizeof(unsigned char );
	datatype[8] = sizeof(float);
	datatype[9] = sizeof(double);
	datatype[10] = sizeof(long double);
	
	for(; i < 10 ; i++)
	{
		fprintf(stdout,"Type: %s  Size: %lu\n",typename[i], datatype[i]);
	
	}

	return 0;
}
