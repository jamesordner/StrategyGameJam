#ifndef GObject_hpp
#define GObject_hpp

#include "Engine.hpp"
#include <vector>
#include <memory>

class GameObject
{
public:
    
    GameObject(const class Engine* engine);
    
    virtual ~GameObject();
    
    /// Create an object component and register it with the corresponding system
    /// Returns an unowned pointer to the created component
    template<typename T>
    T* createComponent() {
        auto* ptr = components.emplace_back(engine->createComponent<T>(this)).get();
        return static_cast<T*>(ptr);
    }
    
    /// Called each frame, with the time since the last frame (ms)
    virtual void tick(uint32_t deltaTime) {};
    
protected:
    
    const class Engine* const engine;
    
private:
    
    std::vector<std::unique_ptr<class GameObjectComponent>> components;
};

#endif /* GObject_hpp */