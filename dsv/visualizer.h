#ifndef visualizer_h
#define visualizer_h

#include "utils.h"
#include "queue.h"

class Visualizer {
private:
    RenderWindow *window;
    
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
        
        return EXIT_SUCCESS;
    }
    
    void events() {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();
            }
            
            if (event.type == Event::MouseButtonPressed) {
                end();
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
        music.openFromFile(resourcePath() + "music.wav");
        music.setVolume(10);
        music.play();
    }
};

#endif /* visualizer_h */
