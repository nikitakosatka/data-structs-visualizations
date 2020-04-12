#ifndef queue_h
#define queue_h

#include "utils.h"

using namespace sf;

class Queue {
private:
    RenderWindow *window;
    
    bool isStarted = false;
    
    Texture bgTexture;
    Texture textTexture;
    Texture shadingTexture;
    
    Animation backgroundAnimation;
    AnimatedSprite background;
    
    Animation shadingAnimation;
    AnimatedSprite shading;
    
    Sprite text;
    
    Sound click;
    SoundBuffer buffer;
    
    Clock frameClock;
    
    Button startBtn;
    Button infoBtn;
    Button nextBtn;
    Button pushBtn;
    Button popBtn;
    Button peekBtn;
    Button arrowsBtn;

public:
    Queue(RenderWindow *window) {
        this->window = window;
        
        loadTextures();
        createSprites();
        
        loadSounds();
    }
    
    void run() {
        begin();
        
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
                if (startBtn.isContainMousePos()) {
                    click.play();
                    isStarted = true;
                } else if (infoBtn.isContainMousePos()) {
                    click.play();
                } else if (nextBtn.isContainMousePos()) {
                    click.play();
                }
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
        
        if (isStarted) {
            start();
        } else {
            window->draw(text);
            
            startBtn.draw();
            infoBtn.draw();
            nextBtn.draw();
        }
        
        window->display();
    }
    
    void loadSounds() {
        buffer.loadFromFile(resourcePath() + "click.wav");
        click.setBuffer(buffer);
    }
    
    void loadTextures() {
        shadingTexture.loadFromFile(resourcePath() + "shading.png");
        bgTexture.loadFromFile(resourcePath() + "queue_background.png");
        textTexture.loadFromFile(resourcePath() + "queue_text.png");
    }
    
    void createSprites() {
        
        // Background init
        backgroundAnimation.setSpriteSheet(bgTexture);
        for (int frame = 0; frame < 22; frame++) {
            backgroundAnimation.addFrame(IntRect(0, frame * HEIGHT, WIDTH, HEIGHT));
        }
        
        background = AnimatedSprite(seconds(0.1), true, true);
        
        // Shading init
        shadingAnimation.setSpriteSheet(shadingTexture);
        for (int frame = 0; frame < 5; frame++) {
            shadingAnimation.addFrame(IntRect(0, frame * HEIGHT, WIDTH, HEIGHT));
        }
        
        shading = AnimatedSprite(seconds(0.1), true, false);
        
        // Title text init
        text = Sprite(textTexture);
        text.setPosition((WIDTH - text.getTextureRect().width) / 2, 50);
        
        // Buttons init
        startBtn = Button(window);
        startBtn.loadTexture(resourcePath() + "queue_start.png");
        startBtn.setPosition((WIDTH - startBtn.getTexture().getSize().x) / 2, 350);
        
        infoBtn = Button(window);
        infoBtn.loadTexture(resourcePath() + "queue_info.png");
        infoBtn.setPosition((WIDTH - infoBtn.getTexture().getSize().x) / 2, 450);
        
        nextBtn = Button(window);
        nextBtn.loadTexture(resourcePath() + "queue_next.png");
        nextBtn.setPosition((WIDTH - nextBtn.getTexture().getSize().x) / 2, 550);
        
        pushBtn = Button(window);
        pushBtn.loadTexture(resourcePath() + "queue_push.png");
        pushBtn.setPosition((WIDTH - pushBtn.getTexture().getSize().x) / 2 + pushBtn.getTexture().getSize().x / 2 + 20, 50);
        
        popBtn = Button(window);
        popBtn.loadTexture(resourcePath() + "queue_pop.png");
        popBtn.setPosition((WIDTH - popBtn.getTexture().getSize().x) / 2 - popBtn.getTexture().getSize().x / 2 - 20, 50);
        
        peekBtn = Button(window);
        peekBtn.loadTexture(resourcePath() + "queue_peek.png");
        peekBtn.setPosition((WIDTH - peekBtn.getTexture().getSize().x) / 2, 550);
        
        arrowsBtn = Button(window);
        arrowsBtn.loadTexture(resourcePath() + "queue_arrows.png");
        arrowsBtn.setPosition((WIDTH - arrowsBtn.getTexture().getSize().x) / 2, 550);
    }
    
    void begin() {
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
            
            startBtn.draw();
            infoBtn.draw();
            nextBtn.draw();
            
            window->display();
        }
    }
    
    void start() {
        popBtn.draw();
        pushBtn.draw();
    }
};


#endif /* queue_h */
