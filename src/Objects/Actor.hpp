#ifndef Actor_hpp
#define Actor_hpp

#include "DrawableObject.hpp"

class Actor : public DrawableObject
{
public:
    
    Actor(const class Engine* engine);
    
    virtual int getRequiredResource(int resource) const { return 0; };
    
    void reduceHealth(int amount);
    
    int getHealth();
    
    void setDestination(const SDL_FPoint& dest);
    
private:
    
    class AIComponent* aiComponent;
    
    unsigned int health;
};

#endif /* Actor_hpp */
