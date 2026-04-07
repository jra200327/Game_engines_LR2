#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <SFML/System/Vector2.hpp>
#include "ICollider.h"

struct BoxColliderComponent : ICollider
{
    float Width;
    float Height;
};

#endif //BOXCOLLIDERCOMPONENT_H