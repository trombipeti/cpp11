#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void leghosszabb()
{
    int maxlen = 0;
    char *buf = (char*)(malloc(sizeof(char) * 2));
    char* leghoszabb;
    buf[0] = '\0';
    buf[1] = '\0';
    char c;
    int curlen = 0;
    while( (c = getchar()) != EOF)
    {
        if(isalpha(c))
        {
            buf[curlen++] = c;
            char* uj = (char*)malloc( (curlen + 1) * sizeof(char));
            int i;
            do
            {
                uj[i] = buf[i];
            } while(buf[i] != 0 && i++ <= curlen);
            
            free(buf);
            buf = uj;
            if(curlen > maxlen)
            {
                maxlen = curlen;
                if(leghosszabb != NULL) free(leghosszabb);
                leghosszabb = (char*)malloc( (maxlen + 1) * sizeof(char) );
                int i;
                do
                {
                    *(leghosszabb + i) = *(buf + i);
                } while(buf[i] != 0 && i++ <= curlen);
                
            }
        }

    }
    if(leghosszabb)
    {
        printf("%s\n", leghoszabb);
    }
    free(buf);
}

int main()
{
    leghosszabb();
    return 0;
}
