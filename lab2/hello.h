#ifndef HELLO_H
#define HELLO_H

#include <stdio.h>

enum Language { language_en, language_hu };

extern enum Language lang;

void hello(int i);
// inline void hello(int i)
// {
//     if(lang == language_en)
//     {
//         printf("Hello %d!\n", i);
//     }
//     else if(lang == language_hu)
//     {
//         printf("Szia %d!\n", i);
//     }
// }
// 

#endif // HELLO_H
