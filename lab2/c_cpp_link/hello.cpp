#include "hello.h"

void hello_cpp(void)
{
    int *a = new int;

    delete a;
}

extern "C" void hello_cpp_helper(void)
{
    hello_cpp();
}
