#ifndef Physics_hpp
#define Physics_hpp

#include "../Engine/GameSystem.hpp"
#include <SDL_rect.h>
#include <vector>

class Physics : public GameSystem
{
public:
    
    Physics(const class Engine* engine);
    
    bool execute(uint32_t deltaTime) override;
    void registerComponent(class GameObjectComponent* component) override;
    void unregisterComponent(class GameObjectComponent* component) override;
    
    /// Returns the GameObject at the given world coordinates, or nullptr if failed
    class GameObject* objectAt(const SDL_Point& coords) const;
    
private:
    
    /// All registered Physics components
    std::vector<class PhysicsComponent*> physicsComponents;
    
    SDL_FPoint getForce(const class PhysicsComponent* component) const;
    
    bool colliding(const class PhysicsComponent* a, const class PhysicsComponent* b) const;
    
    /// World-space bounding box
    SDL_Rect componentBounds(const class PhysicsComponent* component) const;
};

#endif /* Physics_hpp */
