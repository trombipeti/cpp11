#include <iostream>

class TimeInterval
{
    unsigned long long m_;
public:
    explicit TimeInterval(unsigned long long m = 0ULL) :  m_{m} {}
    operator unsigned long long () const { return m_; }
};

TimeInterval operator"" _m(unsigned long long n)
{
    return TimeInterval{n};
}

TimeInterval operator"" _h(unsigned long long n)
{
    return TimeInterval{n*60};
}

TimeInterval operator+(TimeInterval const &lhs, TimeInterval const &rhs)
{
    return TimeInterval{(unsigned long long)lhs + (unsigned long long)rhs};
}

std::ostream& operator<<(std::ostream& os, const TimeInterval& ti)
{
    os << ti/60 << "h " << ti % 60 << "m";
    return os;
}

int main()
{
    TimeInterval i1{65};            /* percben */
    std::cout << i1 << std::endl;   /* 1h 5m */

    TimeInterval i2 = 5_h + 79_m;
    std::cout << i2 << std::endl;   /* 6h 19m */
    return 0;
}