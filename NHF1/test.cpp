#include <iostream>

#include "string.h"

#ifdef _DEBUG_
int String::_Num_Instances = 0;
#endif

int main( int argc, char *argv[] )
{
//    String a, b, c;
//    a = b = c = "helló világ";
//    String rvalos( String {"rvalue vagyok"} );
//    std::cout << a << " " << b << " " << c << " " << rvalos <<  std::endl;
//    a = "alma";
//    b = "fa";
//    String catted = a + b;
    String catted = "Almafa";
    std::cout << catted << std::endl;
    catted += " virága";
    std::cout << catted << std::endl;
    String helloka {String{"Rvalue konstruktor"}};
    std::cout << helloka << std::endl;
    std::cin >> catted;
    std::cout << catted << std::endl;
    String toAdd;
    std::cin >> toAdd;
    catted += toAdd;
    std::cout << catted << std::endl;
    return 0;
}

