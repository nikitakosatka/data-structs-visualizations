#ifndef deque_h
#define deque_h

#include "utils.h"

class Deque {
private:
    RenderWindow *window;
    
    bool isRunning = true;
    bool isStarted = false;
    bool isInfo = false;
    bool isAnimation = false;
    int elementsNum = 0;
    
    Texture bgTexture;
    Texture textTexture;
    Texture elementTexture;
    Texture infoTextTexture;
    
    Animation backgroundAnimation;
    AnimatedSprite background;
    
    Sprite text;
    Sprite infoText;
    Sprite elements[MAX_ELEMENTS];
    
    Sound click;
    SoundBuffer buffer;
    
    Clock frameClock;
    
    Button startBtn;
    Button infoBtn;
    Button nextBtn;
    Button pushBtn;
    Button popBtn;
    Button peekBtn;
    Button xBtn;
    
public:
    Deque(RenderWindow *window) {
        this->window = window;
        
        loadTextures();
        createSprites();
        
        loadSounds();
    }
    
    Deque() = default; // Default constructor
    
    void run() {
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
        }
    }
    
    void update() {
        window->clear();
        
        Time frameTime = frameClock.restart();
        
        background.play(backgroundAnimation);
        background.update(frameTime);
        
        window->draw(background);
        
        for (int el = 0; el < elementsNum + 1; el++) {
            window->draw(elements[el]);
        }
        
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
        bgTexture.loadFromFile(resourcePath() + "deque_background.png");
        textTexture.loadFromFile(resourcePath() + "deque_text.png");
        infoTextTexture.loadFromFile(resourcePath() + "deque_info_text.png");
    }
    
    void createSprites() {
        // Background init
        backgroundAnimation.setSpriteSheet(bgTexture);
        for (int frame = 0; frame < 10; frame++) {
            backgroundAnimation.addFrame(IntRect(0, frame * HEIGHT, WIDTH, HEIGHT));
        }
        
        background = AnimatedSprite(seconds(0.1), true, true);
        
        // Title text init
        text = Sprite(textTexture);
        text.setPosition((WIDTH - text.getTextureRect().width) / 2, 50);
        
        // Info text init
        infoText = Sprite(infoTextTexture);
        infoText.setPosition((WIDTH - infoTextTexture.getSize().x) / 2, (HEIGHT - infoTextTexture.getSize().y) / 2);
        
        // Buttons init
        startBtn = Button(window);
        startBtn.loadTexture(resourcePath() + "deque_start.png");
        startBtn.setPosition((WIDTH - startBtn.getTexture().getSize().x) / 2, 350);
        
        infoBtn = Button(window);
        infoBtn.loadTexture(resourcePath() + "deque_info.png");
        infoBtn.setPosition((WIDTH - infoBtn.getTexture().getSize().x) / 2, 450);
        
        nextBtn = Button(window);
        nextBtn.loadTexture(resourcePath() + "deque_next.png");
        nextBtn.setPosition((WIDTH - nextBtn.getTexture().getSize().x) / 2, 550);
        
        popBtn = Button(window);
        popBtn.loadTexture(resourcePath() + "deque_pop.png");
        popBtn.setPosition((WIDTH / 3 / 2) - 45, 50);
        
        pushBtn = Button(window);
        pushBtn.loadTexture(resourcePath() + "deque_push.png");
        pushBtn.setPosition((WIDTH - pushBtn.getTexture().getSize().x) / 2, 50);
        
        peekBtn = Button(window);
        peekBtn.loadTexture(resourcePath() + "deque_peek.png");
        peekBtn.setPosition(WIDTH / 3 * 2 - 40, 50);
        
        xBtn = Button(window);
        xBtn.loadTexture(resourcePath() + "deque_x.png");
        xBtn.setPosition(50, 50);
    }
    
    void next() {
        for (int frame = 0; frame < 5; frame++) {
            events();
            window->clear();
            
            Time frameTime = frameClock.restart();
            
            background.play(backgroundAnimation);
            background.update(frameTime);
            
            window->draw(background);
            window->draw(text);
            
            startBtn.draw();
            infoBtn.draw();
            nextBtn.draw();
            
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
        
    }
    
    void pop() {
        
    }
    
    void peek() {
        
    }
};



#endif /* deque_h */
