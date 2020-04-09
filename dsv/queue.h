#ifndef queue_h
#define queue_h

#include "utils.h"

using namespace sf;

class Queue {
private:
    RenderWindow *window;
    
    Animation backgroundAnimation;
    AnimatedSprite background;

public:
    Queue(RenderWindow *window) {
        this->window = window;
    }
    
    void run() {
        std::cout << 1 << std::endl;
    }
    
    void events() {
        
    }
    
    void update() {
        
    }
};


#endif /* queue_h */
