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

    Vec2 a (1,0);
    a.normalize();
    std::cout << "Normalized vec: " << a.x << ", " << a.y << std::endl;
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