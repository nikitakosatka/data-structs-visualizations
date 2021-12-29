#ifndef utils_h
#define utils_h

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AnimatedSprite/Animation.hpp"
#include "AnimatedSprite/AnimatedSprite.hpp"

#define pass (void)0

#define WIDTH 1280
#define HEIGHT 720
#define FRAMERATE 60

using namespace std;
using namespace sf;

class Button {
private:
    RenderWindow *window;
    
    Texture texture;
    Sprite button;
    Text text;
    Font font;
    
    float x;
    float y;

public:
    Button() = default; // Default constructor
    
    Button(RenderWindow *window) {
        this->window = window;
    }
    
    Texture getTexture() {
        return texture;
    }
    
    bool isContainMousePos() {
        return (button.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y));
    }
    
    float getPositionX() {
        return x;
    }
    
    float getPositionY() {
        return y;
    }
 
    void loadTexture(string path) {
        if (!texture.loadFromFile(path)) {
            cout << "Error loading texture" << endl;
        }
        
        button = Sprite(texture);
    }
    
    void loadTexture(Texture texture) {
        this->texture = texture;
        button = Sprite(texture);
    }
    
    void setPosition(float x, float y) {
        this->x = x;
        this->y = y;
        button.setPosition(x, y);
    }
    
    void setDefaultPos(float x, float y) {
        this->x = x;
        this->y = y;
    }
    
    void setScale(float factorX, float factorY) {
        button.setScale(factorX, factorY);
    }
    
    void draw() {
        scaleIfMouseContain(x, y);
        window->draw(button);
        window->draw(text);
    }
    
    void scaleIfMouseContain(float x, float y) {
        if (isContainMousePos()) {
            setScale(1.1, 1.1);
            setPosition(x - texture.getSize().x * 0.05, y - texture.getSize().y * 0.05);
            setDefaultPos(x, y);
        } else {
            setScale(1, 1);
            setPosition(x, y);
        }
    }
    
    void setText(string text) {
        this->text.setString(text);
        this->text.setPosition(x, y);
    }
};

#endif /* utils_h */
