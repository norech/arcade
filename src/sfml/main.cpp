/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** main
*/

#include "SfmlGraphic.hpp"
#include "spc/common/DLType.hpp"

extern "C" {
const char* getName(void) { return "SFML"; }
arc::DLType getType(void) { return arc::DLType::GRAPHICAL; }
arc::grph::IGraphic* expose(void) { return new arc::grph::SfmlGraphic(); }
void unexpose(arc::grph::IGraphic* g) { delete g; }
}
