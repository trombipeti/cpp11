#include <iostream>

#include "string.h"

#ifdef _DEBUG_
int String::_Num_Instances = 0;
#endif

int main( int argc, char *argv[] )
{
    String a, b, c;
    a = b = c = "helló világ";
    String rvalos(String{"rvalue vagyok"});
    std::cout << a << " " << b << " " << c << " " << rvalos <<  std::endl;
    return 0;
}

