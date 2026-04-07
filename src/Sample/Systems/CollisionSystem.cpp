#include "CollisionSystem.h"

void CollisionSystem::Print(int ent1, int ent2)
{
    std::cout << ent1 << " collided with: " << ent2 << std::endl;
}

void CollisionSystem::OnInit()
{

}

void CollisionSystem::OnUpdate()
{   
    for (const auto ent : _collideables)
    {
        auto& collision = _collisionComponents.Get(ent);
        collision.CollisionEntities.clear();
    }

    for (auto it1 = _collideables.begin(); it1 != _collideables.end(); ++it1)
    {
        auto ent1 = *it1;

        auto& position1 = _positionComponents.Get(ent1);
        auto& boxCollider1 = _boxColliderComponents.Get(ent1);
        auto& collision1 = _collisionComponents.Get(ent1);

        auto it2 = it1;
        ++it2;

        for (; it2 != _collideables.end(); ++it2)
        {
            auto ent2 = *it2;

            auto& position2 = _positionComponents.Get(ent2);
            auto& boxCollider2 = _boxColliderComponents.Get(ent2);
            auto& collision2 = _collisionComponents.Get(ent2);

            if(position1.Y < position2.Y + boxCollider2.Height && position2.Y < position1.Y + boxCollider1.Height &&
                position1.X < position2.X + boxCollider2.Width && position2.X < position1.X + boxCollider1.Width)
                {
                    collision1.CollisionEntities.push_back(ent2);
                    collision2.CollisionEntities.push_back(ent1);
                    Print(ent1, ent2);
                }
        }
    }
}