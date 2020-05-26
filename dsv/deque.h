#ifndef deque_h
#define deque_h

#include "utils.h"

#define MAX_ELEMENTS_DEQUE 4

class Deque {
private:
    RenderWindow *window;
    
    bool isRunning = true;
    bool isStarted = false;
    bool isInfo = false;
    bool isAnimation = false;
    int elementsBackNum = -1;
    int elementsFrontNum = 0;
    
    Texture bgTexture;
    Texture textTexture;
    Texture elementTexture;
    Texture infoTextTexture;
    Texture wallTexture;
    Texture backTexture;
    Texture frontTexture;
    
    Animation backgroundAnimation;
    AnimatedSprite background;
    
    Sprite text;
    Sprite infoText;
    Sprite wall;
    Sprite back;
    Sprite front;
    Sprite elementsBack[MAX_ELEMENTS / 2];
    Sprite elementsFront[MAX_ELEMENTS / 2];
    
    Sound click;
    SoundBuffer buffer;
    
    Clock frameClock;
    
    Button startBtn;
    Button infoBtn;
    Button nextBtn;
    Button pushBackBtn;
    Button pushFrontBtn;
    Button popBackBtn;
    Button popFrontBtn;
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
                    } else if (pushBackBtn.isContainMousePos()) {
                        click.play();
                        (!isAnimation) ? pushBack() : pass; // if animation doesn't occur, push, else do nothing
                    } else if (popBackBtn.isContainMousePos()) {
                        click.play();
                        (!isAnimation) ? popBack() : pass; // if animation doesn't occur, pop, else do nothing
                    } else if (pushFrontBtn.isContainMousePos()) {
                        click.play();
                        (!isAnimation) ? pushFront() : pass; // if animation doesn't occur, push, else do nothing
                    } else if (popFrontBtn.isContainMousePos()) {
                        click.play();
                        (!isAnimation) ? popFront() : pass; // if animation doesn't occur, pop, else do nothing
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
        
        for (int el = elementsFrontNum; el > 0; el--) {
            window->draw(elementsFront[el]);
        }
        
        for (int el = 0; el < elementsBackNum + 1; el++) {
            window->draw(elementsBack[el]);
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
        bgTexture.loadFromFile(resourcePath() + "deque_background.png");
        textTexture.loadFromFile(resourcePath() + "deque_text.png");
        infoTextTexture.loadFromFile(resourcePath() + "deque_info_text.png");
        wallTexture.loadFromFile(resourcePath() + "deque_wall.png");
        elementTexture.loadFromFile(resourcePath() + "deque_element.png");
        backTexture.loadFromFile(resourcePath() + "deque_back.png");
        frontTexture.loadFromFile(resourcePath() + "deque_front.png");
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
        
        // Wall image init
        wall = Sprite(wallTexture);
        wall.setPosition(0, 354);
        
        // Back and Front titles init
        back = Sprite(backTexture);
        back.setPosition(WIDTH / 3 * 2 - 40, 50);
        
        front = Sprite(frontTexture);
        front.setPosition(WIDTH / 3 * 2 - 40, 150);
        
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
        
        popBackBtn = Button(window);
        popBackBtn.loadTexture(resourcePath() + "deque_pop.png");
        popBackBtn.setPosition((WIDTH / 3 / 2) - 45, 50);
        
        pushBackBtn = Button(window);
        pushBackBtn.loadTexture(resourcePath() + "deque_push.png");
        pushBackBtn.setPosition((WIDTH - pushBackBtn.getTexture().getSize().x) / 2, 50);
        
        popFrontBtn = Button(window);
        popFrontBtn.loadTexture(resourcePath() + "deque_pop.png");
        popFrontBtn.setPosition((WIDTH / 3 / 2) - 45, 150);
        
        pushFrontBtn = Button(window);
        pushFrontBtn.loadTexture(resourcePath() + "deque_push.png");
        pushFrontBtn.setPosition((WIDTH - pushFrontBtn.getTexture().getSize().x) / 2, 150);
        
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
            window->draw(wall);
            
            startBtn.draw();
            infoBtn.draw();
            nextBtn.draw();
            
            window->display();
        }
    }
    
    void start() {
        popBackBtn.draw();
        pushBackBtn.draw();
        popFrontBtn.draw();
        pushFrontBtn.draw();
        
        window->draw(back);
        window->draw(front);
        
        xBtn.draw();
    }
    
    void info() {
        window->draw(infoText);
        xBtn.draw();
    }
    
    void pushBack() {
        isAnimation = true;
        
        if (elementsBackNum < MAX_ELEMENTS_DEQUE) {
            elementsBackNum++;
        
            elementsBack[elementsBackNum] = Sprite(elementTexture);
            
            for (int x = 0; x < 560 - (elementTexture.getSize().x - 42) * elementsBackNum; x += 4) {
                events();
                window->clear();
                
                Time frameTime = frameClock.restart();
                
                background.play(backgroundAnimation);
                background.update(frameTime);
                
                elementsBack[elementsBackNum].setPosition(x, 507);
                
                window->draw(background);
                
                start(); // draw buttons
                
                for (int el = elementsFrontNum; el > 0; el--) {
                    window->draw(elementsFront[el]);
                }
                
                for (int el = 0; el < elementsBackNum + 1; el++) {
                    window->draw(elementsBack[el]);
                }
                
                window->draw(wall);
                
                window->display();
            }
        }
        
        isAnimation = false;
    }
    
    void popBack() {
        isAnimation = true;
        
        if (elementsBackNum >= 0) {
            elementsBackNum--;
            
            for (int x = elementsBack[elementsBackNum + 1].getPosition().x; x > 0; x -= 4) {
                events();
                window->clear();
                
                Time frameTime = frameClock.restart();
                
                background.play(backgroundAnimation);
                background.update(frameTime);
                
                elementsBack[elementsBackNum + 1].setPosition(x, 507);
                
                window->draw(background);
                
                start(); // draw buttons
                
                for (int el = elementsFrontNum; el > 0; el--) {
                    window->draw(elementsFront[el]);
                }
                
                for (int el = 0; el < elementsBackNum + 2; el++) {
                    window->draw(elementsBack[el]);
                }
                
                window->draw(wall);
                
                window->display();
            }
        }
        
        isAnimation = false;
    }
    
    void pushFront() {
        isAnimation = true;
        
        if (elementsFrontNum < MAX_ELEMENTS / 2) {
            if (elementsBackNum == -1) {
                pushBack();
            } else {
                elementsFrontNum++;
                
                elementsFront[elementsFrontNum] = Sprite(elementTexture);
                
                for (int x = WIDTH; x > 560 + (elementTexture.getSize().x - 42) * elementsFrontNum; x -= 4) {
                    events();
                    window->clear();
                    
                    Time frameTime = frameClock.restart();
                    
                    background.play(backgroundAnimation);
                    background.update(frameTime);
                    
                    elementsFront[elementsFrontNum].setPosition(x, 507);
                    
                    window->draw(background);
                    
                    start(); // draw buttons
                    
                    for (int el = elementsFrontNum; el > 0; el--) {
                        window->draw(elementsFront[el]);
                    }
                    
                    for (int el = 0; el < elementsBackNum + 1; el++) {
                        window->draw(elementsBack[el]);
                    }
                    
                    window->draw(wall);
                    
                    window->display();
                }
            }
        }
        
        isAnimation = false;
    }
    
    void popFront() {
        isAnimation = true;
        
        if (elementsFrontNum > 0) {
            elementsFrontNum--;
            
            for (int x = elementsFront[elementsFrontNum + 1].getPosition().x; x < WIDTH; x += 4) {
                events();
                window->clear();
                
                Time frameTime = frameClock.restart();
                
                background.play(backgroundAnimation);
                background.update(frameTime);
                
                elementsFront[elementsFrontNum + 1].setPosition(x, 507);
                
                window->draw(background);
                
                start(); // draw buttons
                
                for (int el = elementsFrontNum + 1; el > 0; el--) {
                    window->draw(elementsFront[el]);
                }
                
                for (int el = 0; el < elementsBackNum + 1; el++) {
                    window->draw(elementsBack[el]);
                }
                
                window->draw(wall);
                
                window->display();
            }
        } else if (elementsBackNum == 0) {
            popBack();
        }
        
        isAnimation = false;
    }
};



#endif /* deque_h */
