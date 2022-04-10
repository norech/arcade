//
// EPITECH PROJECT, 2022
// arcade
// File description:
// cacagraphic
//

#include "CacaGraphic.hpp"
#include "CacaCanvas.hpp"
#include <chrono>
#include <iostream>
#include <thread> // std::this_thread::sleep_for
#include <unordered_map>

namespace arc::grph {

// clang-format off
std::unordered_map<int, KeyCode> CacaGraphic::_keyMap
    = {
        { CACA_KEY_RETURN, KeyCode::ENTER },
        { CACA_KEY_BACKSPACE, KeyCode::BACKSPACE },
        { CACA_KEY_UP, KeyCode::Z },
        { CACA_KEY_DOWN, KeyCode::S },
        { CACA_KEY_LEFT, KeyCode::Q },
        { CACA_KEY_RIGHT, KeyCode::D },
        { ' ', KeyCode::SPACE }
    };
// clang-format on

void CacaGraphic::init()
{
    display = caca_create_display(NULL);
    canvas = caca_get_canvas(display);
    caca_set_display_title(display, "libcaca");
    caca_set_display_time(display, 25000);
    caca_set_color_ansi(canvas, CACA_BLACK, CACA_WHITE);
}

bool CacaGraphic::isOpen()
{
    if (_willBeClosed)
        return false;
    if (display != NULL) {
        return true;
    } else {
        return false;
    }
}

void CacaGraphic::close() { _willBeClosed = true; }

void CacaGraphic::clear() { caca_clear_canvas(canvas); }

void CacaGraphic::render() { caca_refresh_display(display); }

float CacaGraphic::tick() { return 0.025; }

bool CacaGraphic::pollEvent(Event& event)
{
    caca_event_t ev;

    caca_get_event(display, CACA_EVENT_KEY_PRESS | CACA_EVENT_QUIT, &ev, 25);

    if (ev.type == CACA_EVENT_QUIT) {
        event.type = Event::QUIT;
        return true;
    }
    if (ev.type == CACA_EVENT_KEY_PRESS) {
        event.type = Event::EventType::KEYDOWN;
        for (auto& it : _keyMap) {
            if (it.first == ev.data.key.ch) {
                event.keyboardInput.keyCode = it.second;
                return true;
            }
        }
        event.keyboardInput.keyCode = ev.data.key.ch;
        return true;
    }
    return false;
}

void CacaGraphic::loadCanvas(std::shared_ptr<ICanvas>& arcCanvas)
{
    arcCanvas = std::make_shared<CacaCanvas>(this);
}

void CacaGraphic::unloadCanvas(std::shared_ptr<ICanvas>& arcCanvas)
{
    arcCanvas.reset();
}

void CacaGraphic::destroy() { caca_free_display(display); }

int CacaGraphic::getCacaColor(const IColor& code)
{
    switch (code.getColorCode()) {
    case ColorCode::BLACK:
        return CACA_BLACK;
    case ColorCode::RED:
        return CACA_RED;
    case ColorCode::GREEN:
        return CACA_GREEN;
    case ColorCode::YELLOW:
        return CACA_YELLOW;
    case ColorCode::BLUE:
        return CACA_BLUE;
    case ColorCode::MAGENTA:
        return CACA_MAGENTA;
    case ColorCode::CYAN:
        return CACA_CYAN;
    case ColorCode::WHITE:
        return CACA_WHITE;
    default:
        return CACA_BLACK;
    }
}
}
