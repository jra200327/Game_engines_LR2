#include "InputSystem.h"

void InputSystem::OnInit()
{
}

void InputSystem::OnUpdate()
{
    while (const std::optional event = _window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            _window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            const int eventEnt = world.CreateEntity();
            MoveDirection dir = MoveDirection::None;
            if (keyPressed->code == sf::Keyboard::Key::A)
            {
                dir = MoveDirection::Right;
            }
            else if (keyPressed->code == sf::Keyboard::Key::D)
            {
                dir = MoveDirection::Left;
            }

            _eventComponents.Add(eventEnt, MoveInputEvent(dir));
        }
    }
}
