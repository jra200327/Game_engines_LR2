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

   float _minSize;
   float _maxSize;
   float _minSpeed;
   float _maxSpeed;
   float _offset;


public:
    EntityFactory (World &wrld, sf::Texture &tex, float minsiz, float maxsiz, float minsp, float maxsp, float off)
        : _world(wrld), _texture(tex), _minSize(minsiz), _maxSize(maxsiz), _minSpeed(minsp), _maxSpeed(maxsp), _offset(off)
    {
    }

    void CreateEntity(EntityType type, sf::Vector2f pos);

    float RandomFloat(float min, float max);

};

#endif //ENTITYFACTORY_H