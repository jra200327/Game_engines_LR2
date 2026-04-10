#include "Window.h"

#include "../../Sample/Systems/InitSystem.h"
#include "../../Sample/Systems/InputSystem.h"
#include "../../Sample/Systems/MovementSystem.h"
#include "../../Sample/Systems/CollisionSystem.h"
#include "../../Sample/Systems/RenderSystem.h"

Window::Window(const int windowWidth, const int windowHeight): _world()
{
    _window.create(sf::VideoMode({static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)}), "Asteroid");
     auto desktop = sf::VideoMode::getDesktopMode();
    _window.setPosition({ (int) (desktop.size.x / 2 - windowWidth / 2), (int) (desktop.size.y / 2 - windowHeight / 2) });

    _window.setFramerateLimit(60);

    _texture.loadFromFile("..\\..\\Images\\asteroids.png");

    _systems = std::make_shared<SystemsManager>(_world);
    _entityFactory = std::make_shared<EntityFactory>(_world, _texture);

    Initialize();
}

void Window::Initialize()
{
    _systems->AddInitializer(std::make_shared<InitSystem>(_world, _texture, *_entityFactory));
    _systems->AddSystem(std::make_shared<InputSystem>(_world, _window));
    _systems->AddSystem(std::make_shared<MovementSystem>(_world));
    _systems->AddSystem(std::make_shared<CollisionSystem>(_world));
    _systems->AddSystem(std::make_shared<RenderSystem>(_world, _window, _texture));

}

void Window::Run()
{
    while (_window.isOpen()) {
        _window.clear(sf::Color::Black);
        _systems->Update();
        _window.display();
    }
}