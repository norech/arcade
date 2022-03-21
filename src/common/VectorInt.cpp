/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** VectorInt
*/

#include "VectorInt.hpp"

namespace arc::game {

    VectorInt::VectorInt() : _x(0), _y(0)
    {
    }

    VectorInt::VectorInt(int x, int y) : _x(x), _y(y)
    {

    }

    VectorInt::~VectorInt()
    {
    }

    VectorInt &VectorInt::operator+=(VectorInt &vect)
    {
        this->_x += vect._x;
        this->_y += vect._y;
        return (*this);
    }

    VectorInt &VectorInt::operator-=(VectorInt &vect)
    {
        this->_x -= vect._x;
        this->_y -= vect._y;
        return (*this);
    }

    void VectorInt::reset()
    {
        this->_x = 0;
        this->_y = 0;
    }

    void VectorInt::setValue(int x, int y)
    {
        this->_x = x;
        this->_y = y;
    }
}
