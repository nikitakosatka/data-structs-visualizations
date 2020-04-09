#ifndef visualizer_h
#define visualizer_h

#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourcePath.hpp"
#include "AnimatedSprite/AnimatedSprite.hpp"
#include "queue.h"

#define WIDTH 1280
#define HEIGHT 720

using namespace sf;
using namespace std;

class Visualizer {
private:
    RenderWindow *window;
    
    Texture bgTexture;
    Texture textTexture;
    Texture startTexture;
    Texture pressSomewhereTexture;
    
    Sprite text;
    Sprite startButton;
    
    Animation backgroundAnimation;
    AnimatedSprite background;
    
    Animation pressSomewhereAnimation;
    Animation pressSomewhereAnimationStart;
    AnimatedSprite pressSomewhere;
    
    Clock frameClock;
    
public:
    Visualizer(RenderWindow *window) {
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
        
        return EXIT_SUCCESS;
    }
    
    void events() {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();
            }
            
            if (event.type == Event::MouseButtonPressed) {
                Queue queue(window);
                queue.run();
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
        
        pressSomewhere.play(pressSomewhereAnimation);
        pressSomewhere.update(frameTime);
        
        window->draw(background);
        window->draw(text);
        window->draw(pressSomewhere);
        
        window->display();
    }
    
    void loadTextures() {
        Image icon;
        
        icon.loadFromFile(resourcePath() + "icon.png");
        bgTexture.loadFromFile(resourcePath() + "main_background.png");
        textTexture.loadFromFile(resourcePath() + "main_text.png");
        pressSomewhereTexture.loadFromFile(resourcePath() + "press_somewhere_to_start.png");
        
        window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    
    void createSprites() {
        backgroundAnimation.setSpriteSheet(bgTexture);
        for (int frame = 0; frame < 22; frame++) {
            backgroundAnimation.addFrame(IntRect(0, frame * HEIGHT, WIDTH, HEIGHT));
        }
        
        background = AnimatedSprite(seconds(0.08), true, true);
        
        pressSomewhereAnimation.setSpriteSheet(pressSomewhereTexture);
        for (int frame = 0; frame < 15; frame++) {
            pressSomewhereAnimation.addFrame(IntRect(0,
                                                     frame * (pressSomewhereTexture.getSize().y / 20),
                                                     pressSomewhereTexture.getSize().x,
                                                     pressSomewhereTexture.getSize().y / 20));
        }
        
        pressSomewhereAnimationStart.setSpriteSheet(pressSomewhereTexture);
        for (int frame = 15; frame < 20; frame++) {
            pressSomewhereAnimationStart.addFrame(IntRect(0,
                                                          frame * (pressSomewhereTexture.getSize().y / 20),
                                                          pressSomewhereTexture.getSize().x,
                                                          pressSomewhereTexture.getSize().y / 20));
        }
        pressSomewhere = AnimatedSprite(seconds(0.1), true, true);
        pressSomewhere.setPosition((WIDTH - pressSomewhereTexture.getSize().x) / 2, 500);
        
        text = Sprite(textTexture);
        text.setPosition((WIDTH - text.getTextureRect().width) / 2, 50);
        
        startButton = Sprite(startTexture);
        startButton.setPosition((WIDTH - startButton.getTextureRect().width) / 2, 450);
    }
    
    void start() {
        for (float frame = 30; frame >= 1; frame -= 1) {
            events();
            window->clear();
            
            Time frameTime = frameClock.restart();
            
            background.play(backgroundAnimation);
            background.update(frameTime);
            
            
            text.setScale(frame, frame);
            text.setPosition((WIDTH - text.getTextureRect().width * frame) / 2, 50);
            
            window->draw(background);
            window->draw(text);
            window->draw(pressSomewhere);
            sleep(seconds(0.05));
            
            window->display();
        }
        
        pressSomewhere = AnimatedSprite(seconds(0.1), true, false);
        for (int frame = 0; frame < 10; frame++) {
            events();
            window->clear();
            
            Time frameTime = frameClock.restart();
            
            background.play(backgroundAnimation);
            background.update(frameTime);
            
            pressSomewhere.play(pressSomewhereAnimationStart);
            pressSomewhere.update(frameTime);
            
            pressSomewhere.setPosition((WIDTH - pressSomewhereTexture.getSize().x) / 2, 500);
            
            window->draw(background);
            window->draw(text);
            window->draw(pressSomewhere);
            sleep(seconds(0.1));
            
            window->display();
        }
        
        pressSomewhere = AnimatedSprite(seconds(0.1), true, true);
        pressSomewhere.setPosition((WIDTH - pressSomewhereTexture.getSize().x) / 2, 500);
        
    }
};

#endif /* visualizer_h */
