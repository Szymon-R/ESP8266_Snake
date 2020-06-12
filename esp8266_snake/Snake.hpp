#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <Arduino.h>
#include <utility>
#include <array>


enum class Direction
{
    LEFT = 37,
    RIGHT = 39,
    UP = 38,
    DOWN = 40
};

template<uint32_t max_size>
class Snake
{
    public:
        Snake(std::pair<uint32_t, uint32_t> startPoint) : headPosition(startPoint)
        {
            elements[0] = headPosition;
        }

        void Move(Direction dir)
        {
            Serial.println("Move.");
            this->tailPosition = this->elements[this->length-1];
            for (uint32_t i = this->length-1; i > 0; --i)
            {
                this->elements[i] = this->elements[i-1];
            }

            switch (dir)
            {
                case Direction::LEFT :
                    this->headPosition.first -= 1;
                break;
                
                case Direction::RIGHT :
                    this->headPosition.first += 1;
                break;

                case Direction::UP :
                    this->headPosition.second -= 1;
                break;

                case Direction::DOWN:
                    this->headPosition.second += 1;
                break;

                default:

                break;
            }
            elements[0] = this->headPosition;
        }



        bool Consume()
        {
            
        }

        uint32_t GetLength()
        {
            return this->length;
        }

        std::pair<uint32_t, uint32_t>& GiveElement(uint32_t number)
        {
            return this->elements[number];
        }

        void Grow()
        {
            Serial.println("Growing!!");
            if (this->length < max_size-1)
            {
                this->elements[this->length] = this->tailPosition;
                this->length += 1; 
            }
        }

        std::pair<uint32_t, uint32_t> GetHeadPosition()
        {
            return headPosition;
        }

    private:
        static constexpr uint32_t MAX_SIZE = max_size;
        //First one is X-position, second Y-position
        std::pair<uint32_t, uint32_t> headPosition;
        std::pair<uint32_t, uint32_t> tailPosition;
        uint32_t length = 1;
        //First one is X-position, second Y-position
        std::array<std::pair<uint32_t, uint32_t>, MAX_SIZE> elements;
};

#endif