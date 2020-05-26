#ifndef tree_h
#define tree_h

#include "utils.h"

#define MAX_BRANCHES 15
#define MAX_ELEMENTS_TREE 5

class Tree {
private:
    RenderWindow *window;
    
    bool isRunning = true;
    bool isStarted = false;
    bool isInfo = false;
    bool isAnimation = false;
    
    int elementsNum = -1;
    int elementsValues[MAX_BRANCHES];
    
    Texture bgTexture;
    Texture textTexture;
    Texture elementTexture;
    Texture infoTextTexture;
    
    Texture leavesTexture;
    Texture rootTexture;
    Texture firstTexture;
    Texture secondTexture;
    Texture secondEdgeTexture;
    Texture thirdTexture;
    
    Animation backgroundAnimation;
    AnimatedSprite background;
    
    Sprite text;
    Sprite infoText;
    Sprite leaves;
    Sprite branches[MAX_BRANCHES];
    Sprite elements[MAX_BRANCHES][MAX_ELEMENTS_TREE];
    
    Sound click;
    Sound grass;
    SoundBuffer clickBuffer;
    SoundBuffer grassBuffer;
    
    Clock frameClock;
    
    Button startBtn;
    Button infoBtn;
    Button nextBtn;
    Button pushBtn;
    Button popBtn;
    Button peekBtn;
    Button xBtn;
    
public:
    Tree(RenderWindow *window) {
        this->window = window;
        
        loadTextures();
        createSprites();
        
        loadSounds();
    }
    
    Tree() = default; // Default constructor
    
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
                        grass.play();
                        (!isAnimation) ? push() : pass; // if animation doesn't occur, push, else do nothing
                    } else if (popBtn.isContainMousePos()) {
                        grass.play();
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
        
        for (int branch = 0; branch < elementsNum + 1; branch++) {
            window->draw(branches[branch]);
        }
        
        for (int branch = 0; branch < elementsNum + 1; branch++) {
            for (int el = 0; el < elementsValues[branch]; el++) {
                window->draw(elements[branch][el]);
            }
        }
        
        if (elementsNum >= 0) {
            window->draw(leaves);
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
        clickBuffer.loadFromFile(resourcePath() + "click.wav");
        click.setBuffer(clickBuffer);
        
        grassBuffer.loadFromFile(resourcePath() + "grass.wav");
        grass.setBuffer(grassBuffer);
    }
    
    void loadTextures() {
        bgTexture.loadFromFile(resourcePath() + "tree_background.png");
        textTexture.loadFromFile(resourcePath() + "tree_text.png");
        infoTextTexture.loadFromFile(resourcePath() + "tree_info_text.png");
        elementTexture.loadFromFile(resourcePath() + "tree_leaf.png");
        
        // Tree image textures
        rootTexture.loadFromFile(resourcePath() + "tree_root.png");
        leavesTexture.loadFromFile(resourcePath() + "tree_leaves.png");
        firstTexture.loadFromFile(resourcePath() + "tree_first.png");
        secondTexture.loadFromFile(resourcePath() + "tree_second.png");
        secondEdgeTexture.loadFromFile(resourcePath() + "tree_second_edge.png");
        thirdTexture.loadFromFile(resourcePath() + "tree_third.png");
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
        
        // Leaves image init
        leaves = Sprite(leavesTexture);
        leaves.setPosition((WIDTH - leavesTexture.getSize().x) / 2, 50);
        
        // Buttons init
        startBtn = Button(window);
        startBtn.loadTexture(resourcePath() + "tree_start.png");
        startBtn.setPosition((WIDTH - startBtn.getTexture().getSize().x) / 2, 350);
        
        infoBtn = Button(window);
        infoBtn.loadTexture(resourcePath() + "tree_info.png");
        infoBtn.setPosition((WIDTH - infoBtn.getTexture().getSize().x) / 2, 450);
        
        nextBtn = Button(window);
        nextBtn.loadTexture(resourcePath() + "tree_next.png");
        nextBtn.setPosition((WIDTH - nextBtn.getTexture().getSize().x) / 2, 550);
        
        popBtn = Button(window);
        popBtn.loadTexture(resourcePath() + "tree_pop.png");
        popBtn.setPosition((WIDTH / 3 / 2) - 45, 50);
        
        pushBtn = Button(window);
        pushBtn.loadTexture(resourcePath() + "tree_push.png");
        pushBtn.setPosition((WIDTH - pushBtn.getTexture().getSize().x) / 2, 50);
        
        peekBtn = Button(window);
        peekBtn.loadTexture(resourcePath() + "tree_peek.png");
        peekBtn.setPosition(WIDTH / 3 * 2 - 40, 50);
        
        xBtn = Button(window);
        xBtn.loadTexture(resourcePath() + "tree_x.png");
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
        if (elementsNum < MAX_BRANCHES) {
            elementsNum++;
            
            elementsValues[elementsNum] = rand() % MAX_ELEMENTS_TREE + 1;
            
            for (int el = 0; el <= elementsNum; el++) {
                cout << elementsValues[el] << " ";
            } cout << endl;
            
            if (elementsNum == 0) {
                int x = (WIDTH - rootTexture.getSize().x) / 2;
                int y = HEIGHT - rootTexture.getSize().y;
                
                branches[elementsNum] = Sprite(rootTexture);
                branches[elementsNum].setPosition(x, y);
                
                for (int el = 0; el < elementsValues[elementsNum]; el++) {
                    int elementX = (WIDTH - elementTexture.getSize().x) / 2;
                    int elementY = HEIGHT - elementTexture.getSize().y * 2;
                    
                    elements[elementsNum][el] = Sprite(elementTexture);
                    elements[elementsNum][el].setPosition(elementX, elementY);
                    elements[elementsNum][el].rotate(-(el - 3) * 30);
                }
            // костылетрон
            } else {
                if (elementsNum == 1) {
                    firstLevel();
                } else if (elementsNum == 2) {
                    if (elementsValues[elementsNum - 1] >= elementsValues[0] && elementsValues[2] < elementsValues[0]) {
                        firstLevel();
                    } else {
                        secondLevel();
                    }
                } else if (elementsNum == 3) {
                    if ((elementsValues[1] >= elementsValues[0] && elementsValues[2] >= elementsValues[0]) ||
                        (elementsValues[1] < elementsValues[0] && elementsValues[2] < elementsValues[0])) {
                        firstLevel();
                    } else if ((elementsValues[2] >= elementsValues[0] && elementsValues[1] < elementsValues[0]) ||
                               (elementsValues[1] >= elementsValues[0] && elementsValues[2] < elementsValues[0])) {
                        secondLevel();
                    }
                }
            }
        }
    }
    
    void firstLevel() {
        int elementX;
        int elementY;
        
        branches[elementsNum] = Sprite(firstTexture);
        
        if (elementsValues[elementsNum] < elementsValues[0]) {
            elementX = 350;
            elementY = 450;
            
            branches[elementsNum].setPosition(elementX, elementY);
            branches[elementsNum].setOrigin({branches[elementsNum].getLocalBounds().width, 0});
            branches[elementsNum].setScale({-1, 1});
        } else {
            elementX = 650;
            elementY = 480;
            branches[elementsNum].setPosition(elementX, elementY);
            
            elementX += branches[elementsNum].getTexture()->getSize().x;
        }
        
        for (int el = 0; el < elementsValues[elementsNum]; el++) {
            elements[elementsNum][el] = Sprite(elementTexture);
            elements[elementsNum][el].setPosition(elementX, elementY);
            elements[elementsNum][el].rotate(-(el - 3) * 30);
        }
    }
    
    void secondLevel() {
        int elementX;
        int elementY;
        
        if (elementsValues[elementsNum - 1] >= elementsValues[elementsNum - 2]) {
            if (elementsValues[elementsNum] >= elementsValues[elementsNum - 1]) {
                elementX = 1050;
                elementY = 430;
                
                branches[elementsNum] = Sprite(secondEdgeTexture);
                branches[elementsNum].setPosition(850, 430);
            } else {
                elementX = 850;
                elementY = 420;
                
                branches[elementsNum] = Sprite(secondTexture);
                branches[elementsNum].setPosition(850, 420);
            }
        } else {
            if (elementsValues[elementsNum] >= elementsValues[elementsNum - 1]) {
                elementX = 350;
                elementY = 370;
                
                branches[elementsNum] = Sprite(secondTexture);
                branches[elementsNum].setPosition(350, 370);
            } else {
                elementX = 350;
                elementY = 430;
                
                branches[elementsNum] = Sprite(secondEdgeTexture);
                branches[elementsNum].setPosition(350, 430);
                branches[elementsNum].setOrigin({branches[elementsNum].getLocalBounds().width, 0});
                branches[elementsNum].setScale({-1, 1});
            }
        }
        
        for (int el = 0; el < elementsValues[elementsNum]; el++) {
            elements[elementsNum][el] = Sprite(elementTexture);
            elements[elementsNum][el].setPosition(elementX, elementY);
            elements[elementsNum][el].rotate(-(el - 3) * 30);
        }
    }
    
    void pop() {
        if (elementsNum >= 0) {
            elementsNum--;
        }
    }
    
    void peek() {
        if (elementsNum >= 0) {
            for (int frame = 0; frame < 20; frame += 1) {
                events();
                window->clear();
                
                Time frameTime = frameClock.restart();
                
                background.play(backgroundAnimation);
                background.update(frameTime);
                                
                window->draw(background);
                
                for (int el = 0; el < elementsValues[0]; el++) {
                    elements[0][el].rotate(5);
                    
                    for (int branch = 0; branch < elementsNum + 1; branch++) {
                        window->draw(branches[branch]);
                    }
                    
                    for (int branch = 0; branch < elementsNum + 1; branch++) {
                        for (int el = 0; el < elementsValues[branch]; el++) {
                            window->draw(elements[branch][el]);
                        }
                    }
                }
                
                if (elementsNum >= 0) {
                    window->draw(leaves);
                }
                
                start(); // draw buttons
                
                window->display();
            }
        }
    }
};


#endif /* tree_h */
