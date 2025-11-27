#include <iostream>
#include <vector>

int main(int argc, char * argv[])
{
    std::vector<int> vec;
    vec.push_back(42);
    vec.push_back(10); // Per a afegir valors

    std::cout << vec[0] << "\n";
    std::cout << vec[1] << "\n";
    std::cout << vec[2] << std::endl; // Printea lo que te la memoria no te perque ser algo com en C

    for (size_t i=0; i<vec.size(); i++) // Size_t es unsigned int en 32 bit system i 64 bit se adapta
    {
        std::cout << vec[i] << "\n";
    }

    for (int a : vec) // Es com el in de Python
    {
        std::cout << a << "\n";
    }


    std::vector<float> vec_f;
    vec_f.push_back(42.2f); // la f es Floating point??
    vec_f.push_back(32.4f);

    for (auto a : vec) // Fica a en la type que tinga vec
    {
        std::cout << a << "\n";
    }

    return 0;
}