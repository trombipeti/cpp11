#include <stdio.h>
#include "hello.h"

enum Language lang = language_hu;

extern inline void hello(int);

void hello(int i)
{
    if(lang == language_en)
    {
        printf("Hello %d!\n", i);
    }
    else if(lang == language_hu)
    {
        printf("Szia %d!\n", i);
    }
}
