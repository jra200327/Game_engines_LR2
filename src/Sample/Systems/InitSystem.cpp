#include "InitSystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/CollisionComponent.h"

void InitSystem::OnInit()
{
    const int player1 = world.CreateEntity();
    const int player2 = world.CreateEntity();
    auto& positionsStorage = world.GetStorage<PositionComponent>();
    auto& movementsStorage = world.GetStorage<MovementComponent>();
    auto& boxColliderStorage = world.GetStorage<BoxColliderComponent>();
    auto& collisionStorage = world.GetStorage<CollisionComponent>();

    positionsStorage.Add(player1, PositionComponent(0, 0));
    movementsStorage.Add(player1, MovementComponent(5, sf::Vector2f(0, 1)));
    boxColliderStorage.Add(player1, BoxColliderComponent(10, 10));
    collisionStorage.Add(player1, CollisionComponent());
}
