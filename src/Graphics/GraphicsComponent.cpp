#include "GraphicsComponent.hpp"
#include "Sprite.hpp"
#include "Renderer.hpp"

GraphicsComponent::GraphicsComponent(class GameObject* owner) :
    GameObjectComponent(owner)
{
}

GraphicsComponent::~GraphicsComponent()
{
}

void GraphicsComponent::setRenderer(const Renderer* renderer)
{
    this->renderer = renderer;
}

void GraphicsComponent::setSprite(int width, int height, SDL_Color color)
{
    
    auto* pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    Uint32 mappedColor = SDL_MapRGBA(pixelFormat, color.r, color.g, color.b, color.a);
    SDL_FreeFormat(pixelFormat);
    sprite = std::make_unique<Sprite>(renderer->sdlRenderer(), SDL_Rect{ 0, 0, .w = width, .h = height }, mappedColor);
}

void GraphicsComponent::draw(const SDL_Point& cameraPosition)
{
    if (!sprite) return;
    SDL_Rect dest = sprite->bounds;
    dest.x -= cameraPosition.x;
    dest.y -= cameraPosition.y;
    renderer->draw(sprite->texture, dest, 0);
}
