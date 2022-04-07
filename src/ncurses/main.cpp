#include <iostream>
#include <ncurses.h>

#include "NcursesGraphic.hpp"
#include "spc/common/DLType.hpp"
#include "spc/graphic/IGraphic.hpp"

extern "C" {
arc::DLType getType(void) { return arc::DLType::GRAPHICAL; }
arc::grph::IGraphic* expose(void) { return new arc::grph::NcursesGraphic(); }
void unexpose(arc::grph::NcursesGraphic* g) { delete g; }
}
