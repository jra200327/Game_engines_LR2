#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

struct SpriteComponent
{
    sf::Vector2i size;
    sf::Vector2i atlasPos;
    sf::Sprite sprite;

    SpriteComponent(sf::Vector2i size_, sf::Vector2i atlasPos_, const sf::Texture& tex)
        : size(size_),
          atlasPos(atlasPos_),
          sprite(tex)
    {}

    SpriteComponent() : sprite(*(sf::Texture*)nullptr) {}
    
};

#endif //SPRITECOMPONENT_H
