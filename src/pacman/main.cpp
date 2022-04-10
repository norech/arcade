#include "PacmanGame.hpp"
#include "spc/common/DLType.hpp"
#include "spc/game/IGame.hpp"

extern "C" {
const char* getName(void) { return "Pac-man"; }
arc::DLType getType(void) { return arc::DLType::GAME; }
arc::game::IGame* expose(void) { return new arc::game::PacmanGame(); }
void unexpose(arc::game::IGame* game) { delete game; }
}
