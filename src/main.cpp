#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Ecs/Systems/SystemsManager.h"
#include "Ecs/World/World.h"

#include "Sample/Systems/InitSystem.h"
#include "Sample/Systems/InputSystem.h"
#include "Sample/Systems/MovementSystem.h"
#include "Sample/Systems/CollisionSystem.h"
#include "Sample/Systems/RenderSystem.h"

int main() {
    setlocale(LC_ALL, "");

    const int wWidth = 1280;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "Test");
    window.setFramerateLimit(60);

    sf::Texture texture;
    texture.loadFromFile("..\\..\\Images\\asteroids.png");

    World world;
    SystemsManager systems(world);
    EntityFactory entityFactory(world, texture);
    systems.AddInitializer(std::make_shared<InitSystem>(world, texture, entityFactory));
    systems.AddSystem(std::make_shared<InputSystem>(world, window));
    systems.AddSystem(std::make_shared<MovementSystem>(world));
    systems.AddSystem(std::make_shared<CollisionSystem>(world));
    systems.AddSystem(std::make_shared<RenderSystem>(world, window, texture));

    window.clear(sf::Color::Black);

    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        systems.Update();
        window.display();
    }

    return 0;
}