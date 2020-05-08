#ifndef queue_h
#define queue_h

#include "utils.h"

#define MAX_ELEMENTS 16
#define ELEMENT_X 570
#define ELEMENT_Y 415

using namespace sf;

class Queue {
private:
    RenderWindow *window;
    
    bool isStarted = false;
    bool isInfo = false;
    int elementsNum = 0;
    
    Texture bgTexture;
    Texture textTexture;
    Texture shadingTexture;
    Texture elementTexture;
    Texture wallTexture;
    Texture infoTextTexture;
    
    Animation backgroundAnimation;
    AnimatedSprite background;
    
    Animation shadingAnimation;
    AnimatedSprite shading;
    
    Animation elementStayAnimation;
    Animation elementRunAnimation;
    AnimatedSprite element;
    AnimatedSprite elements[MAX_ELEMENTS];
    
    Sprite text;
    Sprite wall;
    Sprite infoText;
    
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
    Button xBtn;

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
                if (isStarted) {
                    if (xBtn.isContainMousePos()) {
                        click.play();
                        isStarted = false;
                    } else if (pushBtn.isContainMousePos()) {
                        click.play();
                    } else if (popBtn.isContainMousePos()) {
                        click.play();
                    }
                } else {
                    if (startBtn.isContainMousePos()) {
                        click.play();
                        isStarted = true;
                    } else if (infoBtn.isContainMousePos()) {
                        click.play();
                    } else if (nextBtn.isContainMousePos()) {
                        click.play();
                    }
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
        
        for (int el = 0; el < elementsNum; el++) {
            elements[el].setPosition(el * 120 + ELEMENT_X, ELEMENT_Y);
            elements[el].play(elementStayAnimation);
            elements[el].update(frameTime);
            window->draw(elements[el]);
        }
        
        window->draw(wall);
        
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
        elementTexture.loadFromFile(resourcePath() + "queue_red.png");
        wallTexture.loadFromFile(resourcePath() + "queue_wall.png");
        infoTextTexture.loadFromFile(resourcePath() + "queue_info_text.png");
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
        
        // Elements init
        elementRunAnimation.setSpriteSheet(elementTexture);
        for (int frame = 0; frame < 4; frame++) {
            elementRunAnimation.addFrame(IntRect(frame * elementTexture.getSize().x / 4, 0,
                                                 elementTexture.getSize().x / 4, elementTexture.getSize().y));
        }
        
        elementStayAnimation.setSpriteSheet(elementTexture);
        elementStayAnimation.addFrame(IntRect(0, 0,
                                              elementTexture.getSize().x / 4, elementTexture.getSize().y));
        
        for (int el = 0; el < MAX_ELEMENTS; el++) {
            elements[el] = AnimatedSprite(seconds(0.1), true, true);
            elements[el].setPosition(el * 120 + ELEMENT_X, ELEMENT_Y);
        }
        
        // Title text init
        text = Sprite(textTexture);
        text.setPosition((WIDTH - text.getTextureRect().width) / 2, 50);
        
        // Wall init
        wall = Sprite(wallTexture);
        wall.setPosition(274, 272);
        
        // Info text init
        infoText = Sprite(infoTextTexture);
        infoText.setPosition((WIDTH - infoTextTexture.getSize().x) / 2, (HEIGHT - infoTextTexture.getSize().y) / 2);
        
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
        
        xBtn = Button(window);
        xBtn.loadTexture(resourcePath() + "queue_x.png");
        xBtn.setPosition(50, 50);
        xBtn.setText("x");
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
        xBtn.draw();
    }
};


#endif /* queue_h */
