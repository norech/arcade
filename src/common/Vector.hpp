/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** Vector
*/

#pragma once

#include "spc/common/Vector2.hpp"

namespace arc::game
{
    class Vector
    {
    private:
    public:
        ~Vector() = default;

        virtual void reset(void) {};
        virtual void setValue(int x[[maybe_unused]], int y[[maybe_unused]]) {};

        virtual Vector2 &operator+=(Vector2 &vect [[maybe_unused]]) { return (vect);};
        virtual Vector2 &operator-=(Vector2 &vect [[maybe_unused]]) { return (vect);};
        virtual bool operator==(Vector2 &vect [[maybe_unused]]) { return (false);};
    };

}
