#include "Cell.hpp"


Cell::Cell(uint32_t cellSize) : cellSize(cellSize)
{

}

String Cell::Parse()
{
    String out = "<td style=\"width: "; 
    out += String(cellSize);
    out += "px;";

    if (this->state == Cell::State::SNAKE_ELEMENT)
    {
        out += "background-color: black;";
    }
    else if (this->state == Cell::State::FOOD)
    {
        out += "background-color: orange;";
    }
    
    out += "\"></td>\n"; 
    return out;
}

void Cell::Reset()
{
    this->state = Cell::State::EMPTY;
}