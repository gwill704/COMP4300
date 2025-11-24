#include <iostream>


void pp(int & a)
{
    // Pointer print 
    std::cout << &a << " " << a << " " << sizeof(a) << std::endl;
}



int main(int argc, char * argv[])
{
    int a = 10;
    int b = 25;
    int* pa = &a;
    int* pb = &b;

    *(pb-1) = 17; // Com estan contigus se modifica a perque -1 resta un int, osea 4 bytes

    pp(a);
    pp(b);



    return 0;
}