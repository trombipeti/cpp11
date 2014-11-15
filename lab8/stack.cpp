#include <iostream>

template <typename T>
class Stack
{
public:
    explicit Stack() 
    {
        m_array_size = 1;
        m_array_count = 0;
        m_array = (T*)malloc(sizeof(T));

        std::cout << "Stack ctor\n";
    }
    
    Stack(Stack const &o)
    {
        std::cout << "Stack copy ctor \n";
    }

    void push(T data)
    {
        if(m_array_count == m_array_size)
        {
            resize_array(INC);
        }
        m_array[m_array_count] = data;
        m_array_count++;
        std::cout << "Stack push, no. of elements: " << m_array_count << "\n";
    }

    T pop()
    {
        T ret = m_array[m_array_count - 1];
        
        m_array_count--;
        if(m_array_count < m_array_size/4)
        {
            resize_array(DEC);
        }
        std::cout << "Stack pop, no. of elements: " << m_array_count << "\n";
        return ret; 
    }
    
    Stack& operator=(Stack const &o) = delete;
    
    ~Stack()
    {
        std::cout << "Stack dtor \n";
    }
    

private:
    T* m_array;
    size_t m_array_size;
    size_t m_array_count;
    
    typedef enum ResizeDir
    {
        INC,
        DEC
    } ResizeDir;


    void move_array(T* dest)
    {
        for(int i = 0; i < m_array_count; ++i)
        {
            new (static_cast<void*>(&dest[i])) T{m_array[i]};
            m_array[i].~T();
        }
        delete m_array;
        std::cout << "Move array, m_array_ptr -> dest_ptr: " << m_array << " -> " << dest << "\n";
        m_array = dest;
    }

    void resize_array(ResizeDir d)
    {
        std::cout << "Resize array (" << (d == INC ? "increase" : "decrease") << ")\n";
        if(d == INC)
        {
            m_array_size *= 2;
        }
        else
        {
            m_array_size /= 2;
        }
        T* new_array = (T*)malloc(m_array_size * sizeof(T));
        move_array(new_array);
        std::cout << "New array size: " << m_array_size << "\n";
    }
};


int main(int argc, char *argv[])
{
    Stack<int> int_stack;
    for(int i = 0;i < 10; ++i)
    {
        int_stack.push(i);
    }
    for(int i = 0; i<10;++i)
    {
        std::cout << int_stack.pop() << std::endl;
    }
    return 0;
}
