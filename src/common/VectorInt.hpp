/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** VectorInt
*/

#pragma once

#include "Vector.hpp"

namespace arc::game {

    class VectorInt : public Vector {
        public:
            int _x;
            int _y;
            VectorInt();
            VectorInt(int x, int y);

            ~VectorInt();

            VectorInt &operator+=(VectorInt &vect);
            VectorInt &operator-=(VectorInt &vect);

            void reset(void) override;
            void setValue(int x, int y) override;

        protected:
        private:
    };
}