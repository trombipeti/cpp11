#include <iostream>
#include <vector>

template <typename ITER>
auto find_min(ITER begin, ITER end) -> decltype(*begin) {
    if (begin == end)
        throw "ures";
    auto min = *begin;
    while (++begin != end)
        if (*begin < min)
            min = *begin;
    return min;
}


int main() {
    std::vector<int> v{1,2,5,2,0,5,4,8};
    std::cout << find_min(v.begin(), v.end()) << std::endl;
    return 0;
}
