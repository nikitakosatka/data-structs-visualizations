#ifndef visualizer_h
#define visualizer_h

#include "utils.h"
#include "queue.h"
#include "stack.h"
#include "deque.h"
#include "tree.h"

#include <filesystem>

class Visualizer {
private:
    RenderWindow *window;
    
    bool running = false;
    bool isStarted = false;
    bool isFirstRunning = true;
    
    Music music;
    
    Texture bgTexture;
    Texture textTexture;
    Texture pressSomewhereTexture;
    
    AnimatedSprite text;
    Animation textStatic;
    Animation textAnimationEnd;
    
    Animation backgroundAnimation;
    Animation backgroundAnimationEnd;
    AnimatedSprite background;
    
    Animation pressSomewhereAnimation;
    Animation pressSomewhereAnimationStart;
    Animation pressSomewhereAnimationEnd;
    AnimatedSprite pressSomewhere;
    
    Clock frameClock;
    
    Queue *queue;
    Stack *stack;
    Deque *deque;
    Tree *tree;
    
public:
    Visualizer(RenderWindow *window) {
        this->window = window;
        
        loadTextures();
        createSprites();
        playMusic();
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
                running = false;
                window->close();
            }
            
            if (event.type == Event::MouseButtonPressed) {
                if (isStarted) {
                    running = true;
                    end();
                }
            }
        }
    }
    
    // All structures are created here
    void loop() {
        events();
        
        queue = new Queue(window, isFirstRunning);
        queue->run();
        delete queue;
        
        stack = new Stack(window);
        stack->run();
        delete stack;
        
        deque = new Deque(window);
        deque->run();
        delete deque;
        
        tree = new Tree(window);
        tree->run();
        delete tree;
        
        isFirstRunning = false;
    }
    
    void update() {
        if (running) {
            loop();
            
        } else {
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
    }
    
    void loadTextures() {
        Image icon;

        icon.loadFromFile("data/images/icon.png");
        bgTexture.loadFromFile("data/images/menu/main_background.png");
        textTexture.loadFromFile("data/images/menu/main_text.png");
        pressSomewhereTexture.loadFromFile("data/images/menu/press_somewhere_to_start.png");
        
        window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    
    void createSprites() {
        
        // Background animation init
        backgroundAnimation.setSpriteSheet(bgTexture);
        for (int frame = 0; frame < 22; frame++) {
            backgroundAnimation.addFrame(IntRect(0, frame * HEIGHT, WIDTH, HEIGHT));
        }
        
        backgroundAnimationEnd.setSpriteSheet(bgTexture);
        for (int frame = 0; frame < 5; frame++) {
            backgroundAnimationEnd.addFrame(IntRect(WIDTH, frame * HEIGHT, WIDTH, HEIGHT));
        }
        
        background = AnimatedSprite(seconds(0.08), true, true);
        
        // PressSomewhereToStart caption animation init
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
        
        pressSomewhereAnimationEnd.setSpriteSheet(pressSomewhereTexture);
        for (int frame = 19; frame >= 15; frame--) {
            pressSomewhereAnimationEnd.addFrame(IntRect(0,
                                                        frame * (pressSomewhereTexture.getSize().y / 20),
                                                        pressSomewhereTexture.getSize().x,
                                                        pressSomewhereTexture.getSize().y / 20));
        }
        
        pressSomewhere = AnimatedSprite(seconds(0.1), true, true);
        pressSomewhere.setPosition((WIDTH - pressSomewhereTexture.getSize().x) / 2, 500);
        
        // Title text animation init
        text = AnimatedSprite(seconds(0.1), true, false);
        
        textStatic.setSpriteSheet(textTexture);
        textStatic.addFrame(IntRect(0, textTexture.getSize().y / 5,
                                    textTexture.getSize().x, textTexture.getSize().y / 5));
        
        textAnimationEnd.setSpriteSheet(textTexture);
        for (int frame = 0; frame < 5; frame++) {
            textAnimationEnd.addFrame(IntRect(0,
                                             frame * (textTexture.getSize().y / 5),
                                             textTexture.getSize().x,
                                             textTexture.getSize().y / 5));
        }
    }
    
    void start() {
        for (float frame = 30; frame >= 1; frame -= 1) {
            events();
            window->clear();
            
            Time frameTime = frameClock.restart();
            
            background.play(backgroundAnimation);
            background.update(frameTime);
            
            text.play(textStatic);
            text.setScale(frame, frame);
            text.setPosition((WIDTH - textTexture.getSize().x * frame) / 2, 50);
            
            window->draw(background);
            window->draw(text);
            window->draw(pressSomewhere);
            sleep(seconds(0.05));
            
            window->display();
        }
        
        pressSomewhere.setLooped(false);
        
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
        
        pressSomewhere.setLooped(true);
        
        isStarted = true;
    }
    
    void end() {
        background.setLooped(false);
        pressSomewhere.setLooped(false);
        
        for (int frame = 0; frame < 30; frame++) {
            events();
            window->clear();
            
            Time frameTime = frameClock.restart();
            background.play(backgroundAnimationEnd);
            background.update(frameTime);
            
            pressSomewhere.play(pressSomewhereAnimationEnd);
            pressSomewhere.update(frameTime);
            
            text.play(textAnimationEnd);
            text.update(frameTime);
            
            window->draw(background);
            window->draw(text);
            window->draw(pressSomewhere);
            
            window->display();
        }
    }
    
    void playMusic() {
        music.openFromFile("data/sounds/music.wav");
        music.setVolume(10);
        music.setLoop(true);
        music.play();
    }
};

#endif /* visualizer_h */
