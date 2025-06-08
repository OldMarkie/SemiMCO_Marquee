#pragma once
#include <string>
#include <atomic>
#include "InputHandler.h"

class MarqueeDisplay {
public:
    MarqueeDisplay(std::atomic<bool>& runFlag, InputHandler& handler,
        const std::string& msg, int width, int height, int fps);
    void run();

private:
    std::atomic<bool>& running;
    InputHandler& inputHandler;
    std::string message;
    int screenWidth, screenHeight, fps;

    void drawHeader();
    void drawMessage(int x, int y);
    void drawFooter();
};
