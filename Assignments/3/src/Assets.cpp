#include "Assets.h"

#include "Animation.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <cassert>
#include <iostream>
#include <fstream>

Assets& Assets::Instance()
{
    static Assets assets;
    return assets;
}

void Assets::addTexture(const std::string& textureName, const std::string& path, bool smooth)
{
    m_textureMap[textureName] = sf::Texture();

    if (!m_textureMap[textureName].loadFromFile(std::string(ASSETS_PATH) + path))
    {
        std::cerr << "Could not load texture file: " << path << std::endl;
        m_textureMap.erase(textureName);
    }
    else 
    {
        m_textureMap[textureName].setSmooth(smooth);
        std::cout << "Loaded Texture: " << path << std::endl;
    }
}

void Assets::addAnimation(const std::string& animationName, const std::string& textureName, size_t numberFrames, size_t speedFrames)
{
    m_animationMap[animationName] = Animation(animationName, textureName, numberFrames, speedFrames);
}

void Assets::addFont(const std::string& fontName, const std::string& path)
{
    m_fontMap[fontName] = sf::Font();
    if (!m_fontMap[fontName].openFromFile(std::string(ASSETS_PATH) + path))
    {
        std::cerr << "Could not load font file: " << path << std::endl;
        m_fontMap.erase(fontName);
    }
    else
    {
        std::cout << "Loaded Font: " << path << std::endl;
    }
}

void Assets::loadFromFile(const std::string& path)
{
    std::ifstream file(path);
    std::string str;
    while(file.good())
    {
        file >> str;

        if (str == "Texture")
        {
            std::string name, path;
            file >> name >> path;
            addTexture(name, path);
        }
        else if (str == "Animation")
        {
            std::string name, texture;
            float frames, speed;
            file >> name >> texture >> frames >> speed;
            addAnimation(name, texture, frames, speed);
        }
        else if (str == "Font")
        {
            std::string name, path;
            file >> name >> path;
            addFont(name, path);
        }
    }
}


const sf::Texture& Assets::getTexture(const std::string& textureName) const
{
    return m_textureMap.at(textureName);
}

const Animation& Assets::getAnimation(const std::string& animationName) const
{
    return m_animationMap.at(animationName);
}

const sf::Font& Assets::getFont(const std::string& fontName) const
{
    return m_fontMap.at(fontName);
}

const std::map<std::string, sf::Texture>& Assets::getTextures() const
{
    return m_textureMap;
}
const std::map<std::string, Animation>& Assets::getAnimations() const
{
    return m_animationMap;
}

const std::map<std::string, sf::Font>& Assets::getFonts() const
{
    return m_fontMap;
}