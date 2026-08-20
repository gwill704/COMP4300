#pragma once

template <typename T, typename... TArgs>
void GameEngine::changeScene(const std::string& sceneName, TArgs&&... args)
{ 
    m_currentScene = sceneName;
    if (m_scenes.find(sceneName) == m_scenes.end())
    {
      m_scenes.insert(std::make_pair(m_currentScene, std::make_shared<T>(this, std::forward<TArgs>(args)...)));
    }
}


