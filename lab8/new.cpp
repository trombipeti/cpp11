#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <new>

class my_bad_alloc : public std::bad_alloc
{
public:
    my_bad_alloc(const char* what) : what_(what) {}
    const char* what() const throw() override
    {
        return what_;
    }
private:
    const char* what_;
};

size_t non_freed_count = 0;

void * operator new(size_t siz) throw(std::bad_alloc)
{
    if(siz > 1024*1024)
    {
        throw my_bad_alloc("Cannot allocate more than 1MB");
    }
    void * ret = malloc(siz);
    if(ret == nullptr)
    {
        throw my_bad_alloc("Allocation of memory failed");
    }
    std::cout << "Alloced " << siz << " btye(s) at " << ret << "\n";
    non_freed_count++;
    return ret;
}


void operator delete(void * dst) noexcept
{
    std::cout << "Freed memory at " << dst << "\n";
    free(dst);
    non_freed_count--;
}

void check_mem()
{
    std::cout << "Memory leaked at " << non_freed_count << " places\n";
}

int main()
{
//     std::string h{"hello vilag"};
    try
    {
        int* tomb = new int[1024*1024*2];
        std::string *ph = new std::string{"hello vilag"};
        std::set<int> s{1, 2, 3, 4, 5};
        
        delete ph;
        
    }
    catch(std::bad_alloc& ba)
    {
        std::cerr << ba.what() << std::endl;
    }
    atexit(check_mem);
    return 0;
}
