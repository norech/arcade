#include "CacaGraphic.hpp"
#include <caca.h>
#include <iostream>

extern "C" {
arc::grph::IGraphic* expose(void) { return new arc::grph::CacaGraphic(); }
void unexpose(arc::grph::IGraphic* g) { delete g; }
}
