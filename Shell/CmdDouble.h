#pragma once
#include <vector>
#include "ICommand.h"
class CommandDouble : public IShellCommand {
public:
    CommandDouble(int snowCount = 100);  // width/height 제거
    bool Call(IParam& param) override;


private:
    struct Snowflake {
        int x, y;
    };

    int width;
    int height;
    int snowCount;
    std::vector<Snowflake> snowflakes;

    void detectConsoleSize();  // 추가
    void hideCursor();
    void moveCursor(int x, int y);
    void clearSnow();
    void updateSnow();
    void drawSnow();
};
