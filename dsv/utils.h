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
    
    void scale(float factorX, float factorY) {
        button.scale(factorX, factorY);
    }
    
    void draw() {
        window->draw(button);
    }
};

#endif /* utils_h */
