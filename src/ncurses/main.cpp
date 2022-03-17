#include <iostream>
#include <ncurses.h>

#include "NcursesGraphic.hpp"
#include "spc/graphic/IGraphic.hpp"

extern "C" {
    arc::grph::IGraphic *expose(std::string name, int size_x, int size_y) { return new arc::grph::NcursesGraphic(name, size_x, size_y); }
}
