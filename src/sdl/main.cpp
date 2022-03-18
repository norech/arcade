#include "SdlGraphic.hpp"
#include <SDL2/SDL.h>
#include <iostream>

extern "C" {
arc::grph::IGraphic* expose(std::string name, int size_x, int size_y)
{
    return new arc::grph::SdlGraphic(name, size_x, size_y);
}
}
