#include "Window.h"

#include "../../Sample/Systems/InitSystem.h"
#include "../../Sample/Systems/InputSystem.h"
#include "../../Sample/Systems/MovementSystem.h"
#include "../../Sample/Systems/CollisionSystem.h"
#include "../../Sample/Systems/CollisionResolveSystem.h"
#include "../../Sample/Systems/RenderSystem.h"
#include "../../Sample/Systems/ShootingSystem.h"
#include "../../Sample/Systems/AsteroidSpawnSystem.h"
#include "../../Sample/Systems/BoundariesSystem.h"


Window::Window(const WindowConfig windCfg, const ShooterConfig shootCfg, const ImageConfig imgCfg, const AsteroidConfig astCfg, const SpawnConfig spCfg): _world(), _spawnCd(spCfg.cd)
{
    _window.create(sf::VideoMode({static_cast<unsigned int>(windCfg.width), static_cast<unsigned int>(windCfg.height)}), "Asteroid");
     auto desktop = sf::VideoMode::getDesktopMode();
    _window.setPosition({ (int) (desktop.size.x / 2 - windCfg.width / 2), (int) (desktop.size.y / 2 - windCfg.height / 2) });

    _window.setFramerateLimit(60);

    _texture.loadFromFile(imgCfg.path);

    _systems = std::make_shared<SystemsManager>(_world);
    _entityFactory = std::make_shared<EntityFactory>(_world, _texture, astCfg, shootCfg);

    Initialize();
}

void Window::Initialize()
{
    _systems->AddInitializer(std::make_shared<InitSystem>(_world, _texture, *_entityFactory));
    _systems->AddSystem(std::make_shared<InputSystem>(_world, _window));
    _systems->AddSystem(std::make_shared<MovementSystem>(_world));
    _systems->AddSystem(std::make_shared<CollisionSystem>(_world));
    _systems->AddSystem(std::make_shared<RenderSystem>(_world, _window, _texture));
    _systems->AddSystem(std::make_shared<ShootingSystem>(_world, *_entityFactory));
    _systems->AddSystem(std::make_shared<CollisionResolveSystem>(_world));
    _systems->AddSystem(std::make_shared<AsteroidSpawnSystem>(_world, *_entityFactory, _spawnCd, _window.getSize().x));
    _systems->AddSystem(std::make_shared<BoundariesSystem>(_world, _window));
}

void Window::Run()
{
    while (_window.isOpen()) {
        _window.clear(sf::Color::Black);
        _systems->Update();
        _window.display();

        _world.Flush();
    }
}