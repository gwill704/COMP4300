#include "GameEngine.h"
#include <SFML/Graphics.hpp>

int main()
{
    std::string file = std::string(ASSETS_PATH) + "assets.txt";
    GameEngine game(file);
}