#include "InputSystem.h"

void InputSystem::OnInit()
{
}

void InputSystem::OnUpdate()
{
    // Process window events
    while (const std::optional event = _window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            _window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::A)
            {
                _isRightPressed = true;
            }
            else if (keyPressed->code == sf::Keyboard::Key::D)
            {
                _isLeftPressed = true;
            }
        }
        else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            if (keyReleased->code == sf::Keyboard::Key::A)
            {
                _isRightPressed = false;
            }
            else if (keyReleased->code == sf::Keyboard::Key::D)
            {
                _isLeftPressed = false;
            }
        }
    }
    
    // Create movement event based on held keys
    MoveDirection dir = MoveDirection::None;
    if (_isLeftPressed && !_isRightPressed)
    {
        dir = MoveDirection::Left;
    }
    else if (_isRightPressed && !_isLeftPressed)
    {
        dir = MoveDirection::Right;
    }
    // Optional: handle both pressed (maybe none or some other direction)
    
    if (dir != MoveDirection::None)
    {
        const int eventEnt = world.CreateEntity();
        _eventComponents.Add(eventEnt, MoveInputEvent(dir));
    }
}