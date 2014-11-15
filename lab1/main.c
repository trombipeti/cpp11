#include <stdio.h>
#include "strswap.h"


int main(void)
{
    char a[2000] = { "Írj egy másik sztringcserélő függvényt is, amely segédtömb nélkül működik! Ennek a két sztring karaktereit páronként kell cserélgetnie addig, amíg el nem ért a hosszabbik sztring végéig, beleértve a lezáró nullát is. Legyen ez az strswap2()." };
    char b[2000] = { "Vegyél most két hosszú sztringet, például ebből az útmutatóból két bekezdést, és cseréld meg őket egymilliószor! Linuxon parancssorból a time parancson keresztül futtatva a programot, ki lehet íratni azt, hogy közelítőleg mennyi ideig tartott a végrehajtás. " };
    //     printf("%s %s\n", a, b);
    for(int i = 0;i<10000000;++i)
    {
        strswap2(a, b);
    }
    //     printf("%s %s\n", a, b);
    //     strswap2(a, b);
    //     printf("%s %s\n", a, b);
    return 0;
}
