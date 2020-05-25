#ifndef stack_h
#define stack_h

#include "utils.h"

class Stack {
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
    Texture infoTextTexture;
    Texture wallTexture;
    Texture elementsTextures[5];
    
    Animation backgroundAnimation;
    AnimatedSprite background;
    
    Sprite text;
    Sprite infoText;
    Sprite wall;
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
    Stack(RenderWindow *window) {
        this->window = window;
        
        loadTextures();
        createSprites();
        
        loadSounds();
    }
    
    Stack() = default; // Default constructor
    
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
        
        window->draw(wall);
        
        window->display();
    }
    
    void loadSounds() {
        buffer.loadFromFile(resourcePath() + "click.wav");
        click.setBuffer(buffer);
    }
    
    void loadTextures() {
        shadingTexture.loadFromFile(resourcePath() + "shading.png");
        bgTexture.loadFromFile(resourcePath() + "stack_background.png");
        textTexture.loadFromFile(resourcePath() + "stack_text.png");
        infoTextTexture.loadFromFile(resourcePath() + "stack_info_text.png");
        wallTexture.loadFromFile(resourcePath() + "stack_wall.png");
        
        // Load books textures
        elementsTextures[0].loadFromFile(resourcePath() + "stack_red.png");
        elementsTextures[1].loadFromFile(resourcePath() + "stack_green.png");
        elementsTextures[2].loadFromFile(resourcePath() + "stack_yellow.png");
        elementsTextures[3].loadFromFile(resourcePath() + "stack_blue.png");
        elementsTextures[4].loadFromFile(resourcePath() + "stack_purple.png");
    }
    
    void createSprites() {
        // Background init
        backgroundAnimation.setSpriteSheet(bgTexture);
        for (int frame = 0; frame < 5; frame++) {
            backgroundAnimation.addFrame(IntRect(0, frame * HEIGHT, WIDTH, HEIGHT));
        }
        
        background = AnimatedSprite(seconds(0.1), true, true);
        
        // Title text init
        text = Sprite(textTexture);
        text.setPosition((WIDTH - text.getTextureRect().width) / 2, 50);
        
        // Info text init
        infoText = Sprite(infoTextTexture);
        infoText.setPosition((WIDTH - infoTextTexture.getSize().x) / 2, (HEIGHT - infoTextTexture.getSize().y) / 2);
        
        // Wall init
        wall = Sprite(wallTexture);
        
        // Buttons init
        startBtn = Button(window);
        startBtn.loadTexture(resourcePath() + "stack_start.png");
        startBtn.setPosition((WIDTH - startBtn.getTexture().getSize().x) / 2, 350);
        
        infoBtn = Button(window);
        infoBtn.loadTexture(resourcePath() + "stack_info.png");
        infoBtn.setPosition((WIDTH - infoBtn.getTexture().getSize().x) / 2, 450);
        
        nextBtn = Button(window);
        nextBtn.loadTexture(resourcePath() + "stack_next.png");
        nextBtn.setPosition((WIDTH - nextBtn.getTexture().getSize().x) / 2, 550);
        
        popBtn = Button(window);
        popBtn.loadTexture(resourcePath() + "stack_pop.png");
        popBtn.setPosition((WIDTH / 3 / 2) - 45, 50);
        
        pushBtn = Button(window);
        pushBtn.loadTexture(resourcePath() + "stack_push.png");
        pushBtn.setPosition((WIDTH - pushBtn.getTexture().getSize().x) / 2, 50);
        
        peekBtn = Button(window);
        peekBtn.loadTexture(resourcePath() + "stack_peek.png");
        peekBtn.setPosition(WIDTH / 3 * 2 - 40, 50);
        
        xBtn = Button(window);
        xBtn.loadTexture(resourcePath() + "stack_x.png");
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
            
            elements[elementsNum] = Sprite(elementsTextures[rand() % 5]); // set random texture
            
            int elementHeight = elements[elementsNum].getTexture()->getSize().y;
            
            if (rand() % 2 == 0) { // randomly flip image
                elements[elementsNum].setOrigin({elements[elementsNum].getLocalBounds().width, 0});
                elements[elementsNum].setScale({-1, 1});
            }
            
            int x = 640 + rand() % (elementHeight * 2 + 1) - elementHeight; // set random x
            
            for (int y = 0; y < 660 - elementHeight * elementsNum; y += elementHeight / 2) {
                events();
                window->clear();
                
                Time frameTime = frameClock.restart();
                
                background.play(backgroundAnimation);
                background.update(frameTime);
                
                elements[elementsNum].setPosition(x, y);
                
                window->draw(background);
                
                for (int el = 0; el < elementsNum + 1; el++) {
                    window->draw(elements[el]);
                }
                
                start(); // draw buttons
                
                window->draw(wall);
                
                window->display();
            }
        }
        
        isAnimation = false;
    }
    
    void pop() {
        int elementHeight = elements[elementsNum].getTexture()->getSize().y;
        
        isAnimation = true;
        
        if (elementsNum > 0) {
            elementsNum--;
            
            for (int y = 660 - (elementsNum + 1) * elementHeight; y > 0; y -= elementHeight / 2) {
                events();
                window->clear();
                
                Time frameTime = frameClock.restart();
                
                background.play(backgroundAnimation);
                background.update(frameTime);
                
                elements[elementsNum + 1].setPosition(elements[elementsNum + 1].getPosition().x, y);
                
                window->draw(background);
                
                for (int el = 0; el < elementsNum + 2; el++) {
                    window->draw(elements[el]);
                }
                
                start(); // draw buttons
                
                window->draw(wall);
                
                window->display();
            }
        }
        
        isAnimation = false;
    }
    
    void peek() {
        for (int frame = 0; frame < 30; frame += 1) {
            events();
            window->clear();
            
            Time frameTime = frameClock.restart();
            
            background.play(backgroundAnimation);
            background.update(frameTime);
            
            elements[elementsNum].rotate(12);
            
            window->draw(background);
            
            for (int el = 0; el < elementsNum + 2; el++) {
                window->draw(elements[el]);
            }
            
            start(); // draw buttons
            
            window->draw(wall);
            
            window->display();
        }
    }
};


#endif /* stack_h */
