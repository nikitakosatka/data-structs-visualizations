#ifndef queue_h
#define queue_h

#include "utils.h"

using namespace sf;

class Queue {
private:
    RenderWindow *window;
    
    Texture bgTexture;
    Texture textTexture;
    
    Animation backgroundAnimation;
    AnimatedSprite background;
    
    Sprite text;
    
    Clock frameClock;

public:
    Queue(RenderWindow *window) {
        this->window = window;
        
        loadTextures();
        createSprites();
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
        
        Time frameTime = frameClock.restart();
        
        background.play(backgroundAnimation);
        background.update(frameTime);
        
        window->draw(background);
        window->draw(text);
        
        window->display();
    }
    
    void loadTextures() {
        bgTexture.loadFromFile(resourcePath() + "queue_background.png");
        textTexture.loadFromFile(resourcePath() + "queue_text.png");
    }
    
    void createSprites() {
        backgroundAnimation.setSpriteSheet(bgTexture);
        for (int frame = 0; frame < 22; frame++) {
            backgroundAnimation.addFrame(IntRect(0, frame * HEIGHT, WIDTH, HEIGHT));
        }
        
        background = AnimatedSprite(seconds(0.1), true, true);
        
        text = Sprite(textTexture);
        text.setPosition((WIDTH - text.getTextureRect().width) / 2, 50);
    }
};


#endif /* queue_h */
