#include <iostream>
#include <ncurses.h>

#include "NcursesGraphic.hpp"
#include "spc/graphic/IGraphic.hpp"

extern "C" {
arc::grph::IGraphic* expose(void) { return new arc::grph::NcursesGraphic(); }
void unexpose(arc::grph::NcursesGraphic* g) { delete g; }
}
