#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "Game.h"

int main() 
{
    /////////////////////////////// Testing area
    Vec2 a(2, 0);
    Vec2 b(2, 1);
    Vec2 c(3,5);
    std::cout << "c = (" << c.x << ", " << c.y << ")" << std::endl;





    
    // TEST QUICKNESS
    // Source - https://stackoverflow.com/q
    // Posted by anamika email, modified by community. See post 'Timeline' for change history
    // Retrieved 2025-12-10, License - CC BY-SA 3.0
    clock_t starts = clock();
    std::cout << "distance = " << a.dist(b) << std::endl; /////// HERE IS THE TEST
    clock_t ends = clock();
    double time = (double)(ends - starts);
    std::cout << "time = " << time << std::endl;



    ////////////////////////////////////////////

    Game g("config.txt");
    g.run();
}