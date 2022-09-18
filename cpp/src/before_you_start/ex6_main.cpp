
#include <dlfcn.h> /* dlopen */
#include <dlfcn.h> /* dlopen */


int main(int atrc, char **argv)
{

    void *handle = nullptr;
    
    handle = dlopen("/home/amit/git/cpp/src/before_you_start/libfoo",RTLD_LAZY);

    dlsym(handle, argv[2]); /* argv[2] - name of function */

    return 0;
}