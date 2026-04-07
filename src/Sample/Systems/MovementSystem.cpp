#include "MovementSystem.h"

void MovementSystem::Print(int ent)
{
    auto& position = _positionComponents.Get(ent);

    std::cout << ent << " Pos: " << position.X << ", " << position.Y << std::endl;
}

void MovementSystem::OnInit()
{

}

void MovementSystem::OnUpdate()
{
    for (const auto eventEntity : _moveInputEvents)
    {
        for (const auto ent : _moveables)
        {
            auto& position = _positionComponents.Get(ent);
            auto& movement = _movementComponents.Get(ent);
            auto& event = _moveInputEventComponents.Get(eventEntity);

            if(event.Direction == MoveDirection::Right)
            {
                movement.Direction.x = -1;
            }
            else if (event.Direction == MoveDirection::Left)
            {
                movement.Direction.x = 1;
            }

            position.X += movement.Speed * movement.Direction.x;

            Print(ent);
        }

        world.RemoveEntity(eventEntity);
    }
}
