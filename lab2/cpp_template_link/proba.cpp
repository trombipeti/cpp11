#include <iostream>
#include "less.h"

template double const & less<double>(double const & a, double const & b);

void proba(void)
{
    double x = 0, y = 10;
    std::cout << less(x,y) << std::endl;
}
