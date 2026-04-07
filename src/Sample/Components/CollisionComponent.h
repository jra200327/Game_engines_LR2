#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "ICollider.h"

struct CollisionComponent
{
    std::vector<ICollider> Collisions;
};

#endif //COLLISIONCOMPONENT_H