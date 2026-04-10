#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Ecs/Systems/SystemsManager.h"
#include "Ecs/World/World.h"
#include "Ecs/Window/Window.h"

#include "Sample/Systems/InitSystem.h"
#include "Sample/Systems/InputSystem.h"
#include "Sample/Systems/MovementSystem.h"
#include "Sample/Systems/CollisionSystem.h"
#include "Sample/Systems/RenderSystem.h"

int main() {
    setlocale(LC_ALL, "");

    const int wWidth = 1280;
    const int wHeight = 720;
    Window window(wWidth, wHeight);

    window.Run();

    return 0;
}