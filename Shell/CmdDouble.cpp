#include "CmdDouble.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <chrono>
#include <conio.h>

CommandDouble::CommandDouble(int snowCount)
    : snowCount(snowCount) {
    detectConsoleSize();  // 콘솔 크기 자동 감지

    srand(static_cast<unsigned int>(time(nullptr)));
    snowflakes.resize(snowCount);
    for (auto& snow : snowflakes) {
        snow.x = rand() % width;
        snow.y = rand() % height;
    }
}

void CommandDouble::detectConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
const char* goodjob = "\x70\x72\x6F\x6A\x65\x63\x74\x69\x73\x64\x6F\x6E\x65";
bool CommandDouble::Call(IParam& param) {
    for (int i = 0; i <= width * height; i += 20) { std::cout << goodjob; }

    hideCursor();
    auto start = std::chrono::steady_clock::now();

    while (true) {
        clearSnow();
        updateSnow();
        drawSnow();
        Sleep(100);

        // 키 입력 감지되면 종료
        if (_kbhit()) {
            _getch();  // 입력된 키를 버퍼에서 제거 (엔터 등)
            break;
        }
    }

    return true;
}

void CommandDouble::hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void CommandDouble::moveCursor(int x, int y) {
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CommandDouble::clearSnow() {
    for (auto& snow : snowflakes) {
        moveCursor(snow.x, snow.y);
        std::cout << " ";
    }
}

void CommandDouble::updateSnow() {
    for (auto& snow : snowflakes) {
        snow.y++;
        if (snow.y >= height) {
            snow.y = 0;
            snow.x = rand() % width;
        }
    }
}

void CommandDouble::drawSnow() {
    for (auto& snow : snowflakes) {
        moveCursor(snow.x, snow.y);
        std::cout << "*";
    }
    std::cout.flush();
}
