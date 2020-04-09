#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"
#include "dsv/visualizer.h"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(1280, 720), "Data Structs");
    window.setFramerateLimit(60);

    Visualizer visualizer(&window);
    visualizer.run();

    return 0;
}
