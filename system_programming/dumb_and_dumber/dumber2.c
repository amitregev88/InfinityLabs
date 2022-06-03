#include <stdio.h>
#include <unistd.h>

int i = 8;
int j = 16;
int k = 32;
int main(int argc, char **argv, char **envp)
{
	int *p = &j;
	
	printf("p = %p; *p=%d\n", p, *p);

	sleep(300);

	return 0;
}
