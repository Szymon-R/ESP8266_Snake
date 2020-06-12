#ifndef _CELL_HPP
#define _CELL_HPP

#include <array>
#include <string.h>
#include <cstdio>
#include "Arduino.h"




class Cell
{
    public:
    enum class State
    {
        SNAKE_ELEMENT,
        FOOD,
        EMPTY
    };
    Cell() = default;
    explicit Cell(uint32_t cellSize);
    State state = State::EMPTY;
    String Parse();
    void Reset();

    private:
        uint32_t cellSize = 0;
};

#endif