#include <stdio.h>
#include <unistd.h>

int i = 7;
int j = 12;
int k = 15;
int main(int argc, char **argv, char **envp)
{
	int *p = &j;

	printf("p = %p; *p=%d\n", p, *p);
	
	sleep(300);

	return 0;
}
