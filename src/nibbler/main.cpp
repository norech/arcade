/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** main
*/

#include "NibblerGame.hpp"
#include "spc/game/IGame.hpp"
#include "spc/common/DLType.hpp"

extern "C" {
    const char* getName(void) { return "Nibbler"; }
    arc::DLType getType(void) { return arc::DLType::GAME; }
    arc::game::IGame* expose(void) { return new arc::game::NibblerGame(); }
    void unexpose(arc::game::IGame* game) { delete game; }
}