//
// EPITECH PROJECT, 2022
// arcade
// File description:
// cacagraphic
//

#include "CacaGraphic.hpp"
#include "CacaCanvas.hpp"
#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>  

namespace arc::grph {

CacaGraphic::CacaGraphic()
{

}

CacaGraphic::~CacaGraphic()
{

}

void CacaGraphic::init()
{
    _display = caca_create_display(NULL);
    //if (_display == NULL) {
    //    throw std::runtime_error("Can't create display");
    //}
    _canvas = caca_get_canvas(_display);
    //if (_canvas == NULL) {
    //    throw std::runtime_error("Can't get canvas");
    //}
    caca_set_display_title(_display, "Arcade");
    caca_set_display_time(_display, 250);
    caca_set_color_ansi(_canvas, CACA_BLACK, CACA_WHITE);
}

bool CacaGraphic::isOpen()
{
    if (_display != NULL) {
        return (true);
    } else {
        return (false);
    }
}

void CacaGraphic::close()
{
    caca_free_display(_display);
}


void CacaGraphic::clear()
{
    caca_clear_canvas(_canvas);
}

void CacaGraphic::render()
{
    caca_refresh_display(_display);
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
}

float CacaGraphic::tick()
{
    return 0.025;
}


bool CacaGraphic::pollEvent(Event &event)
{
    caca_event_t ev;

    caca_get_event(_display, CACA_EVENT_KEY_PRESS, &ev, 25);

    if (ev.type == CACA_EVENT_QUIT) {
        event.type = Event::QUIT;
        return true;
    }
    if (ev.type == CACA_EVENT_KEY_PRESS) {
        event.type = Event::EventType::KEYDOWN;
        event.keyboardInput.keyCode = ev.data.key.ch;
        return true;
    }
    return false;
}


void CacaGraphic::loadCanvas(std::shared_ptr<ICanvas> &canvas)
{
    canvas = std::make_shared<CacaCanvas>(this);
}

void CacaGraphic::unloadCanvas(std::shared_ptr<ICanvas> &canvas)
{
    canvas.reset();
}

void CacaGraphic::destroy()
{
    close();
}

}
