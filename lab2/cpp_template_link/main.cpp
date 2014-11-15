#include <iostream>
#include "less.h"

extern template double const & less<double>(double const & a, double const & b);

int main(void)
{
    double a = 8, b = 9;
    std::cout << less(a,b) << std::endl;
    return 0;
}
