#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "imgui.h"
#include "imgui-SFML.h"

#include "../Systems/SystemsManager.h"
#include "../World/World.h"
#include "../Window/Window.h"
#include "../../Sample/Systems/EntityFactory.h"
#include "../ReadConfig/ReadConfig.h"

class Window {
    sf::RenderWindow _window;
    World _world;
    std::shared_ptr<SystemsManager> _systems;
    std::shared_ptr<EntityFactory> _entityFactory;
    sf::Texture _texture;

    sf::Clock _deltaClock;

    bool _isRun;

    void Initialize();
    void UpdateInputLogic();

public:
    Window(const WindowConfig windCfg, const ShooterConfig shootCfg, const ImageConfig imgCfg, const AsteroidConfig astCfg);
    
    void Run();

    sf::RenderWindow& GetWindow()
    {
        return _window;
    }
};

#endif //WINDOW_H