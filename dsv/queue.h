#ifndef queue_h
#define queue_h

#include "utils.h"

using namespace sf;

class Queue {
private:
    RenderWindow *window;
    
    Texture bgTexture;
    Texture textTexture;
    Texture shadingTexture;
    
    Animation backgroundAnimation;
    AnimatedSprite background;
    
    Animation shadingAnimation;
    AnimatedSprite shading;
    
    Sprite text;
    
    Clock frameClock;

public:
    Queue(RenderWindow *window) {
        this->window = window;
        
        loadTextures();
        createSprites();
    }
    
    void run() {
        start();
        
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
        shadingTexture.loadFromFile(resourcePath() + "shading.png");
        bgTexture.loadFromFile(resourcePath() + "queue_background.png");
        textTexture.loadFromFile(resourcePath() + "queue_text.png");
    }
    
    void createSprites() {
        backgroundAnimation.setSpriteSheet(bgTexture);
        for (int frame = 0; frame < 22; frame++) {
            backgroundAnimation.addFrame(IntRect(0, frame * HEIGHT, WIDTH, HEIGHT));
        }
        
        background = AnimatedSprite(seconds(0.1), true, true);
        
        shadingAnimation.setSpriteSheet(shadingTexture);
        for (int frame = 0; frame < 5; frame++) {
            shadingAnimation.addFrame(IntRect(0, frame * HEIGHT, WIDTH, HEIGHT));
        }
        
        shading = AnimatedSprite(seconds(0.1), true, false);
        
        text = Sprite(textTexture);
        text.setPosition((WIDTH - text.getTextureRect().width) / 2, 50);
    }
    
    void start() {
        for (int frame = 0; frame < 30; frame++) {
            events();
            window->clear();
            
            Time frameTime = frameClock.restart();
            
            background.play(backgroundAnimation);
            background.update(frameTime);
            
            shading.play(shadingAnimation);
            shading.update(frameTime);
            
            window->draw(background);
            window->draw(text);
            window->draw(shading);
            
            window->display();
        }
    }
};


#endif /* queue_h */
