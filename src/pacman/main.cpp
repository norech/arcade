#include "PacmanGame.hpp"
#include "spc/game/IGame.hpp"

extern "C" {
arc::game::IGame* expose(void) { return new arc::game::PacmanGame(); }
void unexpose(arc::game::IGame* game) { delete game;}
}


