#include "CacaGraphic.hpp"
#include <caca.h>
#include <iostream>

#include "spc/common/DLType.hpp"

extern "C" {
arc::DLType getType(void) { return arc::DLType::GRAPHICAL; }
arc::grph::IGraphic* expose(void) { return new arc::grph::CacaGraphic(); }
void unexpose(arc::grph::IGraphic* g) { delete g; }
}
