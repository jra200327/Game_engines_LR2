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


Window::Window(const WindowConfig windCfg, const ShooterConfig shootCfg, const ImageConfig imgCfg, const AsteroidConfig astCfg, const SpawnConfig spCfg, const TextConfig txtCfg): 
_world(), _spawnCd(spCfg.cd), _fontPath(txtCfg.path)
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
    _systems->AddSystem(std::make_shared<CollisionResolveSystem>(_world, *this));
    _systems->AddSystem(std::make_shared<AsteroidSpawnSystem>(_world, *_entityFactory, _spawnCd, _window.getSize().x));
    _systems->AddSystem(std::make_shared<BoundariesSystem>(_world, _window));

    uint8_t color[3] = {255, 255, 255};
    _text = std::make_shared<Text>(_fontPath, "0", 40, color);
    float textX = _window.getSize().x/2 - _text->GetCharacterSize();
    _text->SetPosition({textX, (float) _text->GetCharacterSize()});
}

void Window::Run()
{
    while (_window.isOpen()) {
        _window.clear(sf::Color::Black);
        _systems->Update();
        _text->SetText(std::to_string(_score));
        _text->Draw(_window);
        _window.display();

        _world.Flush();
    }
}

void Window::UpdateScore(int i)
{
    _score +=i;
}