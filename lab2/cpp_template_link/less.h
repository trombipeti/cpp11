#ifndef LESS_H
#define LESS_H

template <typename T>
T const & less(T const & a, T const & b) {
    if (a < b)
        return a;
    else
        return b;
}

#endif
