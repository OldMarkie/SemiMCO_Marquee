#include "InputHandler.h"
#include "MarqueeDisplay.h"
#include <iostream>
#include <atomic>

int main() {
    std::atomic<bool> running(true);
    InputHandler inputHandler(running);

    std::string message = "Hello world in marquee!";
    int consoleWidth = 60;
    int consoleHeight = 20;
    int targetFPS = 30;

    inputHandler.start();

    MarqueeDisplay display(running, inputHandler, message, consoleWidth, consoleHeight, targetFPS);
    display.run();

    running = false;
    inputHandler.join();

    std::cout << "\nExited marquee. Goodbye!\n";
    return 0;
}
