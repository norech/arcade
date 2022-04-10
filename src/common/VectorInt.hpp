/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** VectorInt
*/

#pragma once

#include "Vector.hpp"

namespace arc::game {

    class VectorInt : public Vector{
        public:
            Vector2 value;
            VectorInt();
            VectorInt(int x, int y);

            ~VectorInt();

            VectorInt &operator+=(VectorInt &vect);
            VectorInt &operator-=(VectorInt &vect);
            bool operator==(VectorInt &vect2);

            void reset(void);
            void setValue(int x, int y);

        protected:
        private:
    };
}
