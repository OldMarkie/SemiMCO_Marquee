#pragma once
class ScreenUtils {
public:
    static void clearScreen();
#ifndef _WIN32
    static void setNonBlockingInput();
    static void resetInputMode();
#endif
};