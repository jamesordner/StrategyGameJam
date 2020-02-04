#ifndef Engine_hpp
#define Engine_hpp

#include <vector>
#include <memory>

class Engine
{
public:
    
    Engine();
    
    ~Engine();
    
    void init();
    
    void deinit();
    
    void run();
    
    /// Create a GObjectComponent, register it with the appropriate GameSystem, and
    /// pass ownership of the component object to the caller.
    template<typename T>
    std::unique_ptr<T> createComponent(class GameObject* owner) const {
        auto component = std::make_unique<T>(owner);
        registerComponent(component.get());
        return component;
    }
    
    /// Unregisters a component from the GameSystem it is registered to
    void unregisterComponent(class GameObjectComponent* component) const;
    
private:
    
    std::vector<std::unique_ptr<class World>> worlds;
    
    std::unique_ptr<class Graphics> graphics;
    
    std::unique_ptr<class Input> input;
    
    /// Registers a component with the appropriate GameSystem
    void registerComponent(class GameObjectComponent* component) const;
};

#endif /* Engine_hpp */
