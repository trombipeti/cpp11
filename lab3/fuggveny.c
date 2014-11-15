#include <stdio.h>
#include <math.h>

typedef struct Functor
{
    double (*f)(struct Functor*, double);
    double param;
} Functor;

double sin_dx(Functor* functor, double x)
{
    return sin(functor->param * x);
}

double cos_dx(Functor* functor, double x)
{
    return cos(functor->param * x);
}

// enum Consts {
//     W = 79,
//     H = 20,
// };

void clear(int w, int h, char page[h][w]) {
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            page[y][x] = ' ';
}

void plot(int w, int h, char page[h][w], char c, Functor* func) {
    printf("%p\n", (void*)(func->f));
    printf("%p\n", (void*)&(sin_dx));
    for (int x = 0; x < w; ++x) {
        double fx = (x - w/2)/4.0;
        double fy = func->f(func,fx);
        int y = (fy * 4.0) * -1 + h/2;
        if (y >= 0 && y < h)
            page[y][x] = c;
    }
}

void print(int w, int h, char page[h][w]) {
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x)
            putchar(page[y][x]);
        putchar('\n');
    }
}

int main() {
    int w, h;
    scanf("%d", &w);
    scanf("%d", &h);
    
    char page[h][w];
     
    Functor f_sin_dx;
    f_sin_dx.f = sin_dx;
    double d;
    scanf("%lf", &d);
    f_sin_dx.param = d;
    printf("%p\n", (void*)(f_sin_dx.f));
    clear(w,h,page);
    printf("%p\n", (void*)(f_sin_dx.f));
    plot(w,h,page, 'x', &f_sin_dx);
    f_sin_dx.f = cos_dx;
//     printf("%p\n", (void*)(&f_sin_dx.f));
//     plot(w,h,page, '+', &f_sin_dx);
    print(w,h,page);
    return 0; 
}
