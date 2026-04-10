#include "EntityFactory.h"

#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/ShooterComponent.h"

void EntityFactory::CreateEntity(EntityType type, sf::Vector2f pos)
{
    if (type == EntityType::Player)
    {
        const int player1 = _world.CreateEntity();
        auto& positionsStorage = _world.GetStorage<PositionComponent>();
        auto& movementsStorage = _world.GetStorage<MovementComponent>();
        auto& boxColliderStorage = _world.GetStorage<BoxColliderComponent>();
        auto& collisionStorage = _world.GetStorage<CollisionComponent>();
        auto& spriteStorage = _world.GetStorage<SpriteComponent>();
        auto& shooterStorage = _world.GetStorage<ShooterComponent>();

        positionsStorage.Add(player1, PositionComponent(pos.x, pos.y));
        movementsStorage.Add(player1, MovementComponent(10, sf::Vector2f(0, 0)));
        boxColliderStorage.Add(player1, BoxColliderComponent(10, 10));
        collisionStorage.Add(player1, CollisionComponent());
        spriteStorage.Add(player1, SpriteComponent(sf::Vector2i(48, 32), sf::Vector2i(96, 128), _texture, -90));
        shooterStorage.Add(player1, ShooterComponent(60));
    }
    else if(type == EntityType::Bullet)
    {
        const int bullet = _world.CreateEntity();
        auto& positionsStorage = _world.GetStorage<PositionComponent>();
        auto& movementsStorage = _world.GetStorage<MovementComponent>();
        auto& boxColliderStorage = _world.GetStorage<BoxColliderComponent>();
        auto& collisionStorage = _world.GetStorage<CollisionComponent>();
        auto& spriteStorage = _world.GetStorage<SpriteComponent>();

        positionsStorage.Add(bullet, PositionComponent(pos.x, pos.y));
        movementsStorage.Add(bullet, MovementComponent(50, sf::Vector2f(0, -1)));
        boxColliderStorage.Add(bullet, BoxColliderComponent(10, 10));
        collisionStorage.Add(bullet, CollisionComponent());
        spriteStorage.Add(bullet, SpriteComponent(sf::Vector2i(16, 16), sf::Vector2i(224, 144), _texture, -90));
    }
}