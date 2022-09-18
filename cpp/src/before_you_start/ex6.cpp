/*
1. g++ -c -Wall -Werror -fpic ex6.cpp  ---> create an object file 
2. g++ -shared -o libfoo.so ex6.o      ---> create shre object lib 


*/



int Foo()
{
    return 1;
}

int Bla()
{
    return 100;
}
