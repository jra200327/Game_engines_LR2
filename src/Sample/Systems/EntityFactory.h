#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <SFML/Graphics.hpp>

#include "../../Ecs/World/World.h"

enum class EntityType
{
    Player,
    Asteroid,
    Bullet
};

class EntityFactory  {
    
   World &_world;
   sf::Texture &_texture;

public:
    EntityFactory (World &wrld, sf::Texture &tex)
        : _world(wrld), _texture(tex) 
    {
    }

    void CreateEntity(EntityType type, sf::Vector2f pos);

};

#endif //ENTITYFACTORY_H