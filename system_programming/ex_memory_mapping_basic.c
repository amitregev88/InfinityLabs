#include<stdio.h>
#include<stdlib.h>

static void static_func(void);
void Test1(void);
void Test2(void);
int glob_num = 777;
const int glob_num1;
static int glob_stat_num = 14;
static const int c_glob_stat_num = 3333;




main(int argc, char *argv[] , char *envp[])
{
    int *main_heap = malloc(10);
    int num1 = 2;
    const int num11 = 3;
    static int num2 = 4;
    static const int num22 = 43;

    char *str1 = "Amit";
    char str2[] = "Regev";

    printf("address of ptr main_heap:     %p\n",&main_heap);
    printf("address of main_heap:     %p\n",main_heap);
    printf("address of num1:     %p\n",&num1);
    printf("address of num11:     %p\n",&num11);
    printf("address of num2:     %p\n",&num2);
    printf("address of num22:     %p\n",&num22);

    printf("address of ptr str1:     %p\n",&str1);
    printf("address of str1:     %p\n",str1);
   
    printf("address of ptr str2:     %p\n",&str2);
    printf("address of str2:     %p\n",str2);

    printf("address of static_func:     %p\n",&static_func);

    printf("address of Test1 func:     %p\n",&Test1);
    printf("address of Test2 func:     %p\n",&Test2);
    printf("address of main func:     %p\n",&main);

    
    printf("address of glob_num:     %p\n",&glob_num);
    printf("address of glob_num1:     %p\n",&glob_num1);
    printf("address of glob_stat_num:     %p\n",&glob_stat_num);
    printf("address of c_glob_stat_num:     %p\n",&c_glob_stat_num);

    printf("address of argc:    %p\n",&argc);
    printf("address of argv:     %p\n",&argv);
    printf("address of envp:     %p\n",&envp);

    static_func();



    return 0;
}

static void static_func(void)
{
    int num_func = 2;
    int num_func1 = 3;

    printf("address of num_func:     %p\n",&num_func);
    printf("address of num_func1:     %p\n",&num_func1);

    Test1();
}


void Test1(void)
{
    int num_test1 = 34;
    int num_test11 = 44;

    printf("address of num_test1:     %p\n",&num_test1);
    printf("address of num_test11:     %p\n",&num_test11);



    Test2();
}

void Test2(void)
{
    int num_test2 = 324;
    int num_test22 = 424;
    int *heap_test2 = malloc(22);

    printf("address of num_test2:     %p\n",&num_test2);
    printf("address of num_test22:     %p\n",&num_test22);
    printf("address of ptr heap_test2:     %p\n",&heap_test2);
    printf("address of ptr heap_test2:     %p\n",heap_test2);
}