/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** IVector
*/

#pragma once

class IVector {
    public:
        ~IVector() = default;

        virtual void reset(void) = 0;
        virtual void setValue(int x, int y) = 0;

        virtual IVector &operator+=(IVector &vect) = 0;
        virtual IVector &operator-=(IVector &vect) = 0;
};
