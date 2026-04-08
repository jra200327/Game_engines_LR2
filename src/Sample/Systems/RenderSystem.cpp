#include "RenderSystem.h"

void RenderSystem::OnInit()
{

}

void RenderSystem::OnUpdate()
{
    for (auto ent : _drawables)
    {
         auto& position = _positionComponents.Get(ent);
         auto& sprite = _spriteComponents.Get(ent);

         sprite.sprite.setPosition(sf::Vector2f(position.X, position.Y));
         sprite.sprite.setTextureRect(sf::IntRect(sprite.atlasPos, sprite.size));

         _window.draw(sprite.sprite);
    }
}