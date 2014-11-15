#include <iostream>
#include <new>

class Gadget
{
public:
    explicit Gadget(int i = 0) : i_{i} {}
    int i() const { return i_; }
    void set_i(int i) { i_ = i; }
private:
    int i_;
};

class GadgetAllocator
{
private:
    static void* allocate(size_t siz)
    {

    }

    static void free(void * dest) noexcept
    {

    }

    Gadget g_array;
    bool alloced[64] = {false};
};

int main()
{
    Gadget *g = new Gadget(3);
    std::cout << g->i() << std::endl;
    g->set_i(10);
    std::cout << g->i() << std::endl;
    return 0;
}
