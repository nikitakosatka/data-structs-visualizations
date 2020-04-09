#include "dsv/utils.h"
#include "dsv/visualizer.h"

int main() {
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Data Structs");
    window.setFramerateLimit(FRAMERATE);

    Visualizer visualizer(&window);
    visualizer.run();

    return 0;
}
