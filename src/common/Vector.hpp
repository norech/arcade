/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** Vector
*/

#pragma once

#include "spc/game/IVector.hpp"

namespace arc::game
{
    class Vector : public IVector
    {
    private:
    public:
        ~Vector() = default;

        virtual void reset(void) {};
        virtual void setValue(int x[[maybe_unused]], int y[[maybe_unused]]) {};

        virtual IVector &operator+=(IVector &vect [[maybe_unused]]) { return (vect);};
        virtual IVector &operator-=(IVector &vect [[maybe_unused]]) { return (vect);};
    };

}
