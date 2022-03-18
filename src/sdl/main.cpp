#include "SdlGraphic.hpp"
#include <SDL2/SDL.h>
#include <iostream>

extern "C" {
arc::grph::IGraphic* expose(void) { return new arc::grph::SdlGraphic(); }
void unexpose(arc::grph::IGraphic* g) { delete g; }
}
