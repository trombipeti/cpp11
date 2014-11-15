#include <stdio.h>
#include "hello.h"

class Foo
{
public:
    Foo(int i = 0) : valami(i) {}
    ~Foo() {}
private:
    int valami;
};

int main(void)
{
   hello_c();
   return 0; 
}
