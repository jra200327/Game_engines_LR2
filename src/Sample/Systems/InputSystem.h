#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <SFML/Graphics.hpp>

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/MoveInputEvent.h"

class InputSystem : public ISystem {

    sf::RenderWindow& _window; // так делать не надо точно

    ComponentStorage<MoveInputEvent>& _eventComponents;

    bool _isLeftPressed = false;
    bool _isRightPressed = false;

public:
    InputSystem(World &world, sf::RenderWindow& window)
        : ISystem(world),
        _window(window),
        _eventComponents(world.GetStorage<MoveInputEvent>())
    {

    }

    void OnInit() override;

    void OnUpdate() override;
};



#endif //INPUTSYSTEM_H
