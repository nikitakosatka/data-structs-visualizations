#ifndef utils_h
#define utils_h

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResourcePath.hpp"
#include "AnimatedSprite/Animation.hpp"
#include "AnimatedSprite/AnimatedSprite.hpp"

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

public:
    Button() {}
    
    Button(RenderWindow *window) {
        this->window = window;
    }
    
    Texture getTexture() {
        return texture;
    }
    
    bool isContainMousePos() {
        return (button.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y));
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
        button.setPosition(x, y);
    }
    
    void setScale(float factorX, float factorY) {
        button.setScale(factorX, factorY);
    }
    
    void draw() {
        window->draw(button);
    }
    
    void scaleIfMouseContain(float x, float y) {
        if (isContainMousePos()) {
            setScale(1.1, 1.1);
            setPosition((WIDTH - getTexture().getSize().x * 1.1) / 2, y);
        } else {
            setScale(1, 1);
            setPosition(x, y);
        }
    }
};

#endif /* utils_h */
