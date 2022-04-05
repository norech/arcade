#include "SdlGraphic.hpp"
#include "spc/common/DLType.hpp"
#include <SDL2/SDL.h>
#include <iostream>

extern "C" {
arc::DLType getType(void) { return arc::DLType::GRAPHICAL; }
arc::grph::IGraphic* expose(void) { return new arc::grph::SdlGraphic(); }
void unexpose(arc::grph::IGraphic* g) { delete g; }
}
