#include <iostream>

// The first line is a pre-processor directive
// It is used to include a C++ library 
// This particular library is used for input/ output streams
// std::cout to print

int main(int argc, char * argv[]){
// Each C++ program must have a main function which is run 
// Content in {}
// Main function return int
// argc = number of program args
// argv = array of string (char *) args 

std::cout << "Hello, world!\n";

// This line prints string "Hello, world!\n"
// std is a namespace that contains the cout output stream
// namespace is sort of a library or class in java
// the << operator 'pipes' the string to cout 
// can be used to print any base C++ type 
// Semicolon ;
// Case-sensitive


return 0;

// Main has return type of int
// Return 0 if program ran to normal end
// 

}


