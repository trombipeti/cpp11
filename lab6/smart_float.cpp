#include <iostream>

class Float
{
    float val_;
public:
    static float Epsilon;
    Float(float val) : val_(val) {}
    explicit operator float() const { return val_; }
};

float Float::Epsilon = 1e-5;

bool operator<(const Float& lhs, const Float& rhs)
{
    return ((float)lhs + Float::Epsilon) < (float)rhs;
}

bool operator>(const Float& lhs, const Float& rhs)
{
    return rhs < lhs;
}

bool operator<=(const Float& lhs, const Float& rhs)
{
    return ! (lhs > rhs);
}

bool operator>=(const Float& lhs, const Float& rhs)
{
    return ! (lhs < rhs);
}


bool operator!=(const Float& lhs, const Float& rhs)
{
    return rhs < lhs || rhs > lhs;
}

bool operator==(const Float& lhs, const Float& rhs)
{
    return ! (lhs != rhs);
}

Float operator+(const Float& lhs, const Float& rhs)
{
    return (float)lhs + (float)rhs;
}

Float operator-(const Float& lhs, const Float& rhs)
{
    return (float)lhs - (float)rhs;
}

Float operator-(const Float& f)
{
    return -1.0f * (float)f;
}

Float& operator+=(Float& lhs, const Float& rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

Float& operator-=(Float& lhs, const Float& rhs)
{
    lhs = lhs - rhs;
    return lhs;
}

std::ostream& operator<<(std::ostream& os, const Float& rhs)
{
    os << (float)rhs;
    return os;
}


int main()
{
    Float f1 = 1.0f,
    f2 = 1.00001f,
    f3 = 100;

    std::cout << (f1 < f2) << std::endl;    /* hamis */
    std::cout << (f1 < f3) << std::endl;    /* igaz */

    f1 = f2 + f3;

    for (Float f = 0.9999; f < 1.0001; f += 0.00001) {
        std::cout << f << '\t' << (f == 1.0) << std::endl;
    }

    std::cout << -f1 << std::endl; 
    
    return 0;
}