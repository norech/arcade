/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** VectorInt
*/

#include "VectorInt.hpp"

namespace arc::game {

    VectorInt::VectorInt()
    {
        value.x = 0;
        value.y = 0;
    }

    VectorInt::VectorInt(int x, int y)
    {
        value.x = x;
        value.y = y;
    }

    VectorInt::~VectorInt()
    {
    }

    VectorInt &VectorInt::operator+=(VectorInt &vect)
    {
        this->value.x += vect.value.x;
        this->value.y += vect.value.y;
        return (*this);
    }

    VectorInt &VectorInt::operator-=(VectorInt &vect)
    {
        this->value.x  -= vect.value.x;
        this->value.y  -= vect.value.y;
        return (*this);
    }

    bool operator==(VectorInt &vect, VectorInt &vect2)
    {
        if (vect.value.x == vect2.value.x && vect.value.y == vect2.value.y)
            return (true);
        return (false);
    }

    void VectorInt::reset()
    {
        this->value.x = 0;
        this->value.y = 0;
    }

    void VectorInt::setValue(int x, int y)
    {
        this->value.x = x;
        this->value.y = y;
    }
}
