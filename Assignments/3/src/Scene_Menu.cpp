#include "Scene_Menu.h"

Scene_Menu::Scene_Menu(GameEngine* gameEngine) : Scene(gameEngine)
{
  init();
}

void Scene_Menu::init()
{
  registerAction(sf::Keyboard::Scancode::Q,                   "QUIT");
  registerAction(sf::Keyboard::Scancode::S,                   "DOWN");
  registerAction(sf::Keyboard::Scancode::W,                   "UP");
  registerAction(sf::Keyboard::Scancode::Enter,               "SELECT");

  m_level = One;
}

void Scene_Menu::sRender()
{
  m_game->window().clear(sf::Color(50,50,150));

  sf::Vector2f position = { 60, 60 };
  float        delta    = 90;

  sf::Text text(Assets::Instance().getFont("Menu"), "", 40);

  text.setString("level one");
  if (m_level == One)
  {
    text.setFillColor(sf::Color::White);
  }
  else text.setFillColor(sf::Color(80,80,80));
  text.setPosition( position );
  m_game->window().draw(text);

  text.setString("level two");
  if (m_level == Two)
  {
    text.setFillColor(sf::Color::White);
  }
  else text.setFillColor(sf::Color(80,80,80));
  position.y += delta;
  text.setPosition( position );
  m_game->window().draw(text);

  text.setString("level three");
  if (m_level == Three)
  {
    text.setFillColor(sf::Color::White);
  }
  else text.setFillColor(sf::Color(80,80,80));
  position.y += delta;
  text.setPosition( position );  
  m_game->window().draw(text);


  switch (m_level)
  {
    case One:
      m_levelName = "level1";
      break;
    case Two:
      m_levelName = "level2";
      break;
    case Three:
      m_levelName = "level3";
      break;     
  }
  std::string levelPathExtension = ".txt";
  m_levelPath = std::string(ASSETS_PATH) + m_levelName + levelPathExtension;

}

void Scene_Menu::sDoAction(const Action& action)
{
  if (action.type() == "START")
  {
    if      (action.name() == "QUIT"  )                  { m_game->quit(); }
    else if (action.name() == "DOWN"  )                  { m_level = static_cast<Level>((m_level + 1) % (Three + 1)); }
    else if (action.name() == "UP"    )                  { m_level = static_cast<Level>(((Three + 1) + (m_level - 1)) % (Three + 1)); }
    else if (action.name() == "SELECT")                  { m_game->changeScene<Scene_Play>(m_levelName, m_levelPath); }
  }
}

void Scene_Menu::update()
{
  sRender();
}
