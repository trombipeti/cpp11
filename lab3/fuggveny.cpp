#include <iostream>
#include <cmath>

enum Consts {
    W = 79,
    H = 20,
};

class Functor
{
public:
    virtual double operator() (double param) const = 0;
};

class SinFunc : public Functor
{
private:
    double d;
public:
    SinFunc(double d) : d(d) {}
    double operator() (double param) const override { return sin(d*param); }
};

class CosFunc : public Functor
{
private:
    double d;
public:
    CosFunc(double d) : d(d) {}
    double operator() (double param) const override { return cos(d*param); }
};

void clear(char page[H][W]) {
    for (int y = 0; y < H; ++y)
        for (int x = 0; x < W; ++x)
            page[y][x] = ' ';
}

void plot(char page[H][W], char c,const Functor& f) {
    for (int x = 0; x < W; ++x) {
        double fx = (x - W/2)/4.0;
        double fy = f(fx);
        int y = (fy * 4.0) * -1 + H/2;
        if (y >= 0 && y < H)
            page[y][x] = c;
    }
}

void print(char page[H][W]) {
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x)
            putchar(page[y][x]);
        putchar('\n');
    }
}

int main() {
    char page[H][W];
    double d;
    
    std::cin >> d;
    
    SinFunc sinfunc(d);

    std::cin >> d;
    
    CosFunc cosfunc(d);
    
    clear(page);
    plot(page, '.', sinfunc);
    plot(page, '+', cosfunc);
    print(page);
}
