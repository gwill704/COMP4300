#include <iostream>

void pp(int & a)
{
    // Pointer print 
    std::cout << &a << " " << a << " " << sizeof(a) << std::endl;
}

int main(int argc, char * argv[])
{
    //int a = 10;
    //int b = 25;

    int arr[10] = {}; // stack array
    int * harr = new int[10];

    for (size_t i=0; i<10; i++)
    {
        pp(arr[i]);
    }

    for (size_t i=0; i<10; i++)
    {
        pp(harr[i]);
    }
    

    return 0;
}