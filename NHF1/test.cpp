#include <iostream>

#include "string.h"

#ifdef _DEBUG_
int String::_Num_Instances = 0;
#endif

/**
 * A fordításhoz meg kell adni az -fno-elide-constructors paramétert,
 * különben nem tesztelődik ki minden!
 */

int main( int argc, char *argv[] )
{
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
    catted = helloka + ' ';
    catted += 'b';
    std::cout << catted << std::endl;
    helloka = toAdd;
    std::cout << helloka << std::endl;;
    std::cout << "helloka mérete: " << helloka.length() << std::endl;
    return 0;
}

