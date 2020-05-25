#include "dsv/visualizer.h"

int main() {
    srand(time(nullptr));
    
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Data Structs");
    window.setFramerateLimit(FRAMERATE);

    Visualizer visualizer(&window);
    visualizer.run();

    return 0;
}
