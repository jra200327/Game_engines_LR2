#ifndef INITSYSTEM_H
#define INITSYSTEM_H

#include "../../Ecs/Systems/IInitializer.h"
#include <SFML/Graphics/Texture.hpp>

class InitSystem final : public IInitializer {
    sf::Texture &_texture;
public:
    InitSystem(World &world, sf::Texture &texture) : IInitializer(world), _texture(texture) { }

    void OnInit() override;
};



#endif //INITSYSTEM_H
