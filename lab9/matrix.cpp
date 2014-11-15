#include <iostream>
#include <stdexcept>

class Matrix {
public:    
    Matrix() : w_(0), h_(0), data_(nullptr) {}
    
    Matrix(size_t w, size_t h) : w_(w), h_(h)
    {
        data_ = new double[ w_ * h_ ];
        for(int i = 0; i < w_ * h_; ++i)
        {
            data_[i] = 0;
        }
    }

    ~Matrix()
    {
        delete data_;
    }

    double& operator()(size_t y, size_t x)
    {
        if(x <= w_ && y <= h_ && x > 0 && y > 0)
        {
            return data_[(x - 1) * w_ + (y - 1)];
        }
        else
        {
            throw std::out_of_range("A matrixot jol tulindexelted...");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Matrix & m);
    private:
        size_t w_, h_;
        double *data_;
};

std::ostream& operator<<(std::ostream& os, Matrix & m)
{
    for(int i = 1;i <= m.w_; ++i)
    {
        for(int j = 1; j <= m.h_; ++j)
        {
            os << m(j,i);
            os << (j < m.h_ ? ' ' : '\n');
        }
    }
    return os;
}

int main()
{
    Matrix m{3, 3};
    m(1, 1) = 9;  m(2, 3) = 5;
    std::cout << m;
    return 0;
}
