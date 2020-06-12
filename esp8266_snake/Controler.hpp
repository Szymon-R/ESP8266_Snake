#ifndef _CONTROLER_HPP
#define _CONTROLER_HPP

#include <time.h> 

#include "Snake.hpp"
#include "Table.hpp"

extern HardwareSerial Serial;

template<uint32_t max_size, uint32_t rows, uint32_t cols>
class Controler
{
    enum class Result
    {
        SUCCESS,
        BORDER_HIT,
        BODY_HIT
    };

    public:
        Controler(Snake<max_size>& snake, Table<rows, cols>& table)  : table(table), snake(snake)
        {
            
        }

        Controler::Result Execute(Direction dir)
        {   
           
            this->snake.Move(dir);
            this->table.ResetCells();
            if (this->foodPosition == this->snake.GetHeadPosition())
            {
                this->snake.Grow();
                if (!this->foodPresent)
                {
                    this->foodPresent = this->InsertFood();
                    if (!foodPresent)
                    {
                        return Result::SUCCESS;
                    }
                    this->foodPosition = this->table.FindFood();
                }
                
            }
            

            for (int i=0; i < snake.GetLength(); ++i)
            {
                this->table.SetCellState(Cell::State::SNAKE_ELEMENT, snake.GiveElement(i));
            }
            this->table.SetCellState(Cell::State::FOOD, foodPosition);
        }

 /*       Controler::Result Execute()
        {   
            this->table.ResetCells();
            for (int i=0; i < snake.GetLength(); ++i)
            {
                this->table.SetCellState(Cell::State::SNAKE_ELEMENT, snake.GiveElement(i));
            }
        }*/

        void Init()
        {
            srand(time(NULL));
            Serial.println("Init.");
            this->table.ResetCells();
            this->InsertFood();
            this->foodPosition = this->table.FindFood();
        }

    private:

        bool InsertFood()
        {
            Serial.println("Food generated.");
            static_assert(rows * cols < RAND_MAX, "Can't generate food, table is too big!");
            int foodPosition = rand() % table.size;

            for (uint32_t i = 0; i < table.size; ++i)
            {
                if (table.GetCellState(foodPosition) != Cell::State::EMPTY)
                {
                    foodPosition = ((foodPosition + 1) % table.size);
                }
                else
                {
                    table.SetCellState(Cell::State::FOOD, foodPosition);
                    return true;
                }
            }
            return false;
        }
        
        bool CheckBorders();
        bool foodPresent;
        std::pair<uint32_t, uint32_t> foodPosition{0, 0};
        Snake<max_size>& snake;
        Table<rows, cols>& table;
};
#endif