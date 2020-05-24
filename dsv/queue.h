#ifndef queue_h
#define queue_h

#include "utils.h"

#define MAX_ELEMENTS 64
#define ELEMENT_X 570
#define ELEMENT_Y 415

using namespace sf;

class Queue {
private:
    RenderWindow *window;
    
    bool isRunning = true;
    bool isStarted = false;
    bool isInfo = false;
    bool isAnimation = false;
    int elementsNum = 0;
    
    Texture bgTexture;
    Texture textTexture;
    Texture shadingTexture;
    Texture elementTexture;
    Texture wallTexture;
    Texture infoTextTexture;
    
    Animation backgroundAnimation;
    AnimatedSprite background;
    
    Animation shadingAnimationEnd;
    Animation shadingAnimation;
    AnimatedSprite shading;
    
    Animation elementStayAnimation;
    Animation elementRunAnimation;
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
    
    Queue() = default; // Default constructor
    
    void run() {
        begin();
        
        while (window->isOpen() && isRunning) {
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
                        (!isAnimation) ? push() : pass; // if animation doesn't occur, push, else do nothing
                    } else if (popBtn.isContainMousePos()) {
                        click.play();
                        (!isAnimation) ? pop() : pass; // if animation doesn't occur, pop, else do nothing
                    } else if (peekBtn.isContainMousePos()) {
                        click.play();
                        peek();
                    }
                } else if (isInfo) {
                    if (xBtn.isContainMousePos()) {
                        click.play();
                        isInfo = false;
                    }
                } else {
                    if (startBtn.isContainMousePos()) {
                        click.play();
                        isStarted = true;
                    } else if (infoBtn.isContainMousePos()) {
                        click.play();
                        isInfo = true;
                    } else if (nextBtn.isContainMousePos()) {
                        click.play();
                        next();
                        isRunning = false;
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
        } else if (isInfo) {
            info();
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
        
        shadingAnimationEnd.setSpriteSheet(shadingTexture);
        for (int frame = 0; frame < 5; frame++) {
            shadingAnimationEnd.addFrame(IntRect(0, (4 - frame) * HEIGHT, WIDTH, HEIGHT));
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
        
        popBtn = Button(window);
        popBtn.loadTexture(resourcePath() + "queue_pop.png");
        popBtn.setPosition((WIDTH / 3 / 2) - 45, 50);
        
        pushBtn = Button(window);
        pushBtn.loadTexture(resourcePath() + "queue_push.png");
        pushBtn.setPosition((WIDTH - pushBtn.getTexture().getSize().x) / 2, 50);
        
        peekBtn = Button(window);
        peekBtn.loadTexture(resourcePath() + "queue_peek.png");
        peekBtn.setPosition(WIDTH / 3 * 2 - 40, 50);
        
        xBtn = Button(window);
        xBtn.loadTexture(resourcePath() + "queue_x.png");
        xBtn.setPosition(50, 50);
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
            
            startBtn.draw();
            infoBtn.draw();
            nextBtn.draw();
            
            window->draw(shading);
            
            window->display();
        }
    }
    
    void start() {
        popBtn.draw();
        pushBtn.draw();
        peekBtn.draw();
        xBtn.draw();
    }
    
    void info() {
        window->draw(infoText);
        xBtn.draw();
    }
    
    void push() {
        isAnimation = true;
        
        if (elementsNum < MAX_ELEMENTS) {
            elementsNum++;
        
            for (int x = WIDTH; x > ELEMENT_X + 120 * (elementsNum - 1); x -= 4) {
                events();
                window->clear();
                
                Time frameTime = frameClock.restart();
                
                background.play(backgroundAnimation);
                background.update(frameTime);
                
                elements[elementsNum - 1].setPosition(x, ELEMENT_Y);
                
                window->draw(background);
                
                start(); // draw buttons
                
                for (int el = 0; el < elementsNum; el++) {
                    if (el == elementsNum - 1) {
                        elements[el].play(elementRunAnimation);
                    } else {
                        elements[el].play(elementStayAnimation);
                    }
                    elements[el].update(frameTime);
                    window->draw(elements[el]);
                }
                
                window->draw(wall);
                
                window->display();
            }
        }
        
        isAnimation = false;
    }
    
    void pop() {
        bool isAnimation = true;
        
        if (elementsNum > 0) {
            elementsNum--;
            
            for (int x = ELEMENT_X; x > ELEMENT_X - 120 ; x -= 2) {
                events();
                window->clear();
                
                Time frameTime = frameClock.restart();
                
                background.play(backgroundAnimation);
                background.update(frameTime);
                
                for (int el = 0; el < elementsNum + 1; el++) {
                    elements[el].setPosition(x + 120 * el, ELEMENT_Y);
                }
                
                window->draw(background);
                
                start(); // draw buttons
                
                for (int el = 0; el < elementsNum + 1; el++) {
                    elements[el].play(elementRunAnimation);
                    elements[el].update(frameTime);
                    window->draw(elements[el]);
                }
                
                window->draw(wall);
                
                window->display();
            }
        }
        
        isAnimation = false;
    }
    
    void peek() {
        for (int frame = 0; frame < 30; frame++) {
            events();
            window->clear();
            
            Time frameTime = frameClock.restart();
            
            background.play(backgroundAnimation);
            background.update(frameTime);
            
            window->draw(background);
            
            start(); // draw buttons
            
            for (int el = 0; el < elementsNum; el++) {
                if (el == 0) {
                    elements[el].play(elementRunAnimation);
                } else {
                    elements[el].play(elementStayAnimation);
                }
                
                elements[el].update(frameTime);
                window->draw(elements[el]);
            }
            
            window->draw(wall);
            
            window->display();
        }
    }
    
    void next() {
        shading = AnimatedSprite(seconds(0.1), true, false);
        
        for (int frame = 0; frame < 30; frame++) {
            events();
            window->clear();
            
            Time frameTime = frameClock.restart();
            
            background.play(backgroundAnimation);
            background.update(frameTime);
            
            shading.play(shadingAnimationEnd);
            shading.update(frameTime);
            
            window->draw(background);
            window->draw(text);
            
            startBtn.draw();
            infoBtn.draw();
            nextBtn.draw();
            
            window->draw(shading);
            
            window->display();
        }
    }
};


#endif /* queue_h */
