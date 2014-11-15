#include <iostream>
#include <cstdlib>
#include <ctime>

class Ratio
{
    private:
        int m_num, m_den;
    public:
        Ratio(int _num, int _den)
        {
            int a = _num, b = _den, t;
            while (b != 0)
            {
                t = a%b, a = b, b = t;
            }
            m_num = _num/a;
            m_den = _den/a;
        }

        int num() const { return m_num; }
        int den() const { return m_den; }
        
        Ratio& operator=(const Ratio& r);
        
        Ratio& operator+=(const Ratio& r);
        Ratio& operator-=(const Ratio& r);
        
        Ratio& operator*=(const Ratio& r);
        Ratio& operator/=(const Ratio& r);
        
        operator double() const
        {
            return ((double)(m_num)) / m_den; 
        }
};

bool operator==(const Ratio& r1, const Ratio& r2)
{
    return r1.num() == r2.num() && r1.den() == r2.den();
}

Ratio operator+(const Ratio& r1,const Ratio& r2)
{
    return Ratio(r1.num() * r2.den() + r2.num() * r1.den(),
                r1.den() * r2.den());
}

Ratio operator-(const Ratio& r1,const Ratio& r2)
{
    return Ratio(r1.num() * r2.den() - r2.num() * r1.den(),
                r1.den() * r2.den());
}

Ratio operator*(const Ratio& r1, const Ratio& r2)
{
    return Ratio(r1.num() * r2.num(), r2.den() * r2.den());
}

Ratio operator/(const Ratio& r1, const Ratio& r2)
{
    return Ratio(r1.num() * r2.den(), r1.den() * r2.num());
}

Ratio& Ratio::operator=(const Ratio& r)
{
    if(r == *this) return *this;
    else 
    {
        m_num = r.num();
        m_den = r.den();
        return *this;
    }
}

Ratio& Ratio::operator*=(const Ratio& r)
{
    *this = *this * r;
    return *this;
}

Ratio& Ratio::operator/=(const Ratio& r)
{
    *this = *this / r;
    return *this;
}

Ratio& Ratio::operator+=(const Ratio &r)
{
    *this = *this + r;
    return *this;
}

Ratio& Ratio::operator-=(const Ratio &r)
{
    *this = *this - r;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Ratio& r)
{
    os << r.num() << "/" << r.den();
    return os;
}

std::istream& operator>>(std::istream& is, Ratio& r)
{
    int d, n;
    is >> d;
    is >> n;
    r = Ratio(d, n);
    return is;
}

int main(void)
{
    srand(time(NULL));
    Ratio r(3,4), e(1,2);
    std::cout << r + e << std::endl;
    Ratio b = r + e;
    std::cout << "r+e:  " << b << std::endl;
    b += r;
    std::cout << "+=r:" << b << std::endl;
    b = b - r;
    std::cout << "-r:  " << b << std::endl;
    b -= e;
    std::cout << "-=e: " << b << std::endl;
    b = r * Ratio(3,2);
    std::cout << "*(3,2):  " << b << std::endl;
    b *= Ratio(10,4);
    std::cout << "*=(10,4): " << b << std::endl;
    b = b / Ratio(10,4);
    std::cout << "/(10,4): " << b << std::endl;
    b /= e;
    std::cout << "/= e: " << b << std::endl;
    std::cin >> r;
    std::cout << (double)r << std::endl;
    Ratio x(1,2);
    x *= Ratio(10,4);
    Ratio f = x / Ratio(10,4);
    std::cout << f << std::endl;
    return 0;
}
