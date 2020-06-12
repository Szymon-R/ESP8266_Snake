#ifndef _TABLE_HPP
#define _TABLE_HPP

#include "Cell.hpp"
#include <array>
#include <string.h>

template<uint32_t rowsNumber, uint32_t colsNumber>
class Table
{
    public:
        explicit Table(uint32_t cellSize) : cellSize(cellSize)
        {
            //This overwrite cause some overhead,
            //but it makes code cleaner and more readable
            for (uint32_t i = 0; i < rowsNumber * colsNumber; ++i)
            {
                this->cells[i] =  Cell(this->cellSize);
            }
        }
        
        String Parse()
        {
            uint32_t width = this->cols * this->cellSize;
            uint32_t height = this->rows * this->cellSize;
            String out = "<table style=\"height: " + String(height) + "px;\" width=\"" + String(width) + "\">\n";
            out += "<tbody>\n";

            for (uint32_t i = 0U; i < this->rows; ++i)
            {
                out += "<tr>\n";
                for (uint32_t j = 0U; j < this->cols; ++j)
                {
                    out += this->cells[i*this->cols + j].Parse();
                }   
                out += "</tr>\n";
            }
            out += "</tbody>\n";
            out += "</table>\n";
            return out;
        }

        void SetCellState(Cell::State state, std::pair<uint32_t, uint32_t> coordinates)
        {
            this->cells[coordinates.second * this->cols + coordinates.first].state = state;
        }

        void SetCellState(Cell::State state, uint32_t coordinates)
        {
            this->cells[coordinates].state = state;
        }

        Cell::State GetCellState(std::pair<uint32_t, uint32_t> coordinates)
        {
            return this->cells[coordinates.second * this->cols + coordinates.first].state;
        }

        Cell::State GetCellState(uint32_t coordinates)
        {
            return this->cells[coordinates].state;
        }

        void ResetCells()
        {
            for (auto& cell : this->cells)
            {
                cell.Reset();
            }
        }

        std::pair<uint32_t, uint32_t> FindFood()
        {
            for (uint32_t i = 0U; i < this->rows; ++i)
            {
                for (uint32_t j = 0U; j < this->cols; ++j)
                {
                    if (this->cells[i*this->cols + j].state == Cell::State::FOOD)
                    {
                        return std::make_pair(i, j);
                    }
                }   
            }
            return std::make_pair(0, 0);
        }
        
        String Debug()
        {
            String out = "";
            for (uint32_t i=0; i < this->rows; ++i)
            {
                for (uint32_t j=0; j < this->cols; ++j)
                {
                    if (cells[i*this->cols + j].state == Cell::State::EMPTY)
                    {
                        out += "#";
                    }
                    else if (cells[i*this->cols + j].state == Cell::State::FOOD)
                    {
                        out += "*";
                    }
                    else
                    {
                        out += "A";
                    }
                    
                }
                out += "\n";
            }
            out += "\n";
            return out;
        }

        static constexpr uint32_t rows = rowsNumber;
        static constexpr uint32_t cols = colsNumber;
        static constexpr uint32_t size = rows * cols;

    private:
        const uint32_t cellSize;
        std::array<Cell, rowsNumber * colsNumber> cells;

    };

#endif