#pragma once

#include<array>

using permsAry = std::array<bool, 9>;
void disableForward(permsAry& ary);
void disableBackward(permsAry& ary);
void disablePivotTurn(permsAry& ary);
void disableAll(permsAry& ary);
void enableAll(permsAry& ary);

enum EDirection {
    NO_INPUT,
    TOP,
    TOP_RIGHT,
    RIGHT,
    BOTTOM_RIGHT,
    BOTTOM,
    BOTTOM_LEFT,
    LEFT,
    TOP_LEFT
};

struct Operation {
    EDirection direction;
    bool shot;
};
