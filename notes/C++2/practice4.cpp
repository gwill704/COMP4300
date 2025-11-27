#include <iostream>


void pp(int & a)
{
    // Pointer print 
    std::cout << &a << " " << a << " " << sizeof(a) << std::endl;
}


template <typename T> // Generics (codigo per a cambiar cosetes)
class DynamicArray
{
    size_t m_size;
    T * m_arr;

public:

    DynamicArray(size_t size) // Constructor
        : m_size(size)
        , m_arr (new T[size])
    {
        std::cout << "Array Constructor\n";
    }

    ~DynamicArray() // Destructor
    {
        delete [] m_arr;
        std::cout << "Array destructor\n";
    }


    T get(size_t index) const
    {
        return m_arr[index];
    }

    void set(size_t index, T val)
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
   DynamicArray<float> myArray(10);

    myArray.set(4, 123.4);

    myArray.print();

    return 0;
}