#include "InputHandler.h"
#include "ScreenUtils.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#endif

#include <cctype>
#include <chrono>

InputHandler::InputHandler(std::atomic<bool>& runningRef) : running(runningRef) {}

void InputHandler::start() {
    inputThread = std::thread(&InputHandler::processInput, this);
}

void InputHandler::join() {
    if (inputThread.joinable()) inputThread.join();
}

std::string InputHandler::getInputBuffer() {
    std::lock_guard<std::mutex> lock(inputMutex);
    return inputBuffer;
}

std::string InputHandler::getLastInput() {
    std::lock_guard<std::mutex> lock(inputMutex);
    return lastSubmittedInput;
}

void InputHandler::processInput() {
#ifdef _WIN32
    while (running) {
        if (_kbhit()) {
            char ch = _getch();
            handleChar(ch);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
#else
    ScreenUtils::setNonBlockingInput();
    while (running) {
        char ch;
        ssize_t result = read(STDIN_FILENO, &ch, 1);
        if (result > 0) {
            handleChar(ch);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    ScreenUtils::resetInputMode();
#endif
}

void InputHandler::handleChar(char ch) {
    std::lock_guard<std::mutex> lock(inputMutex);
#ifdef _WIN32
    if (ch == '\r') {
#else
    if (ch == '\n') {
#endif
        if (inputBuffer == "q" || inputBuffer == "quit" || inputBuffer == "exit") {
            running = false;
        }
        else if (!inputBuffer.empty()) {
            lastSubmittedInput = inputBuffer;
        }
        inputBuffer.clear();
    }
    else if ((ch == 8 || ch == 127) && !inputBuffer.empty()) {
        inputBuffer.pop_back();
    }
    else if (isprint(ch)) {
        inputBuffer += ch;
    }
    }
