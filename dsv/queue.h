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
        while (window->isOpen()) {
            events();
            update();
        }
    }
    
    void events() {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();
            }
            
            if (event.type == Event::MouseButtonPressed) {
                cout << 1 << endl;
            }
            
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window->close();
            }
        }
    }
    
    void update() {
        window->clear();
        
        window->display();
    }
};


#endif /* queue_h */
