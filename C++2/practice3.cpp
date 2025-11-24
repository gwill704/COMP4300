#include <iostream>


void pp(int & a)
{
    // Pointer print 
    std::cout << &a << " " << a << " " << sizeof(a) << std::endl;
}


class IntArray
{
    size_t m_size;
    int * m_arr;

public:

    IntArray(size_t size) // Constructor
        : m_size(size)
        , m_arr (new int[size])
    {
        std::cout << "Array Constructor\n";
    }

    ~IntArray() // Destructor
    {
        delete [] m_arr;
        std::cout << "Array destructor\n";
    }


    int get(size_t index) const
    {
        return m_arr[index];
    }

    void set(size_t index, int val)
    {
        m_arr[index] = val;
    }

    void print() const
    {
        for (size_t i=0; i<m_size; i++)
        {
            std::cout << i << " " << m_arr[i] << "\n";
        }
    }

};

int main(int argc, char * argv[])
{
   IntArray myArray(10);

    myArray.set(4, 123);

    myArray.print();

    return 0;
}