#include "Scene_Menu.h"

Scene_Menu::Scene_Menu(GameEngine& gameEngine) : Scene(gameEngine)
{
  init();
}

void Scene_Menu::init()
{
  registerAction(sf::Keyboard::Scancode::Escape,              "QUIT");
  registerAction(sf::Keyboard::Scancode::S,                   "DOWN");
  registerAction(sf::Keyboard::Scancode::W,                   "UP");
  registerAction(sf::Keyboard::Scancode::Enter,               "SELECT");
}

void Scene_Menu::sRender()
{
  m_game.window().clear(sf::Color(50,50,150));

  sf::Text text(Assets::Instance().getFont("Menu"), "", 40);
  text.setString("level one");
  text.setFillColor(sf::Color::White);
  text.setPosition( { 50, 50 } );
  
  m_game.window().draw(text);
   // std::string levelPath = std::string(ASSETS_PATH) + "level1.txt";
}

void Scene_Menu::sDoAction(const Action& action)
{
  std::cout << "Scene_Menu::sDoAction : " << action.name() << std::endl;
  
}

void Scene_Menu::update()
{
  std::cout << "Scene_Menu::update : " << std::endl;
  sRender();
}
