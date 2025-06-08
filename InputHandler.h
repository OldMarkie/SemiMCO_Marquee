#pragma once

#include <string>
#include <thread>
#include <mutex>
#include <atomic>

class InputHandler {
public:
    InputHandler(std::atomic<bool>& running);
    void start();
    void join();
    std::string getInputBuffer();
    std::string getLastInput();

private:
    std::atomic<bool>& running;
    std::mutex inputMutex;
    std::string inputBuffer;
    std::string lastSubmittedInput;
    std::thread inputThread;
    void processInput();
    void handleChar(char ch);
};
