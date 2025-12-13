#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "Game.h"

int main() 
{
    /////////////////////////////// Testing area


    // TEST QUICKNESS
    // Source - https://stackoverflow.com/q
    // Posted by anamika email, modified by community. See post 'Timeline' for change history
    // Retrieved 2025-12-10, License - CC BY-SA 3.0

    /*
    clock_t starts = clock();
     /////// HERE IS THE TEST
    clock_t ends = clock();
    double time = (double)(ends - starts);
    std::cout << "time = " << time << std::endl;
    */


    ////////////////////////////////////////////

    Game g("config.txt");
    g.run();
}