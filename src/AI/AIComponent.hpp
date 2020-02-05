#ifndef AIComponent_hpp
#define AIComponent_hpp

#include "../Engine/GameObjectComponent.hpp"
#include <optional>
#include <SDL_rect.h>

class AIComponent : public GameObjectComponent
{
public:
    
    AIComponent(class GameObject* owner);
    
    float movementSpeed;
    
    /// The actor's current movement target
    std::optional<SDL_FPoint> target;
};

#endif /* AIComponent_hpp */
