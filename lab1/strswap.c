#include <string.h>
#include <stdlib.h>

#include "strswap.h"

void strswap(char* a, char* b)
{
    char* longer = (strlen(a) > strlen(b) ? a : b);
    size_t longerlen = strlen(longer);
    char* shorter = (longer == a ? b : a);
    size_t shorterlen = strlen(shorter);
    char* buf = (char*)malloc( (longerlen + 1) * sizeof(char));
    strncpy(buf, longer, longerlen + 1);
    strncpy(longer, shorter, shorterlen + 1);
    strncpy(shorter, buf, strlen(buf) + 1);
    free(buf);
}

void strswap2(char* a, char* b)
{
    char* longer = (strlen(a) > strlen(b) ? a : b);
    char* shorter = (longer == a ? b : a);
    while(*longer)
    {
       char tmp = *shorter;
       *shorter = *longer;
       *longer = tmp;
       longer++; shorter++;
    }
}
