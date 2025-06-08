#include "MarqueeDisplay.h"
#include "ScreenUtils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

MarqueeDisplay::MarqueeDisplay(std::atomic<bool>& runFlag, InputHandler& handler,
    const std::string& msg, int width, int height, int fpsVal)
    : running(runFlag), inputHandler(handler), message(msg),
    screenWidth(width), screenHeight(height), fps(fpsVal) {
}

void MarqueeDisplay::run() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int x = std::rand() % (screenWidth - message.length());
    int y = std::rand() % (screenHeight - 4);
    int dx = 1, dy = 1;
    int frameDelay = 1000 / fps;

    while (running) {
        ScreenUtils::clearScreen();
        drawHeader();
        drawMessage(x, y);
        drawFooter();

        std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay));

        if (x <= 0 || x + message.length() >= screenWidth) dx *= -1;
        if (y <= 0 || y >= screenHeight - 1) dy *= -1;

        x += dx;
        y += dy;
    }
}

void MarqueeDisplay::drawHeader() {
    std::cout << "* Displaying a marquee console! *\n";
    std::cout << std::string(40, '*') << "\n";
}

void MarqueeDisplay::drawMessage(int x, int y) {
    for (int row = 0; row < screenHeight; ++row) {
        if (row == y) {
            std::cout << std::string(x, ' ') << message << "\n";
        }
        else {
            std::cout << "\n";
        }
    }
}

void MarqueeDisplay::drawFooter() {
    std::cout << std::string(40, '*') << "\n";
    std::cout << "Type something (q to quit): " << inputHandler.getInputBuffer() << "\n";
    std::string response = inputHandler.getLastInput();
    if (!response.empty()) {
        std::cout << "You said: " << response << "\n";
    }
}