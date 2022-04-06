//
// EPITECH PROJECT, 2022
// arcade
// File description:
// cacagraphic
//

#include "CacaGraphic.hpp"
#include "CacaCanvas.hpp"
#include "spc/common/KeyCode.hpp"
#include <chrono>
#include <iostream>
#include <thread> // std::this_thread::sleep_for

namespace arc::grph {

CacaGraphic::CacaGraphic() { }

CacaGraphic::~CacaGraphic() { }

void CacaGraphic::init()
{
    _display = caca_create_display(NULL);
    _canvas = caca_get_canvas(_display);
    caca_set_display_title(_display, "libcaca");
    caca_set_display_time(_display, 25000);
    caca_set_color_ansi(_canvas, CACA_BLACK, CACA_WHITE);
}

bool CacaGraphic::isOpen()
{
    if (_willBeClosed)
        return false;
    if (_display != NULL) {
        return true;
    } else {
        return false;
    }
}

void CacaGraphic::close() { _willBeClosed = true; }

void CacaGraphic::clear() { caca_clear_canvas(_canvas); }

void CacaGraphic::render() { caca_refresh_display(_display); }

float CacaGraphic::tick() { return 0.025; }

bool CacaGraphic::pollEvent(Event& event)
{
    caca_event_t ev;

    caca_get_event(_display, CACA_EVENT_KEY_PRESS | CACA_EVENT_QUIT, &ev, 25);

    if (ev.type == CACA_EVENT_QUIT) {
        event.type = Event::QUIT;
        return true;
    }
    if (ev.type == CACA_EVENT_KEY_PRESS) {
        switch (ev.data.key.ch) {
        case CACA_KEY_RETURN:
            event.keyboardInput.keyCode = KeyCode::I;
            break;
        case CACA_KEY_UP:
            event.keyboardInput.keyCode = KeyCode::Z;
            break;
        case CACA_KEY_DOWN:
            event.keyboardInput.keyCode = KeyCode::S;
            break;
        case CACA_KEY_LEFT:
            event.keyboardInput.keyCode = KeyCode::Q;
            break;
        case CACA_KEY_RIGHT:
            event.keyboardInput.keyCode = KeyCode::D;
            break;
        case ' ':
            event.keyboardInput.keyCode = KeyCode::U;
            break;
        default:
            event.keyboardInput.keyCode = ev.data.key.ch;
            break;
        }
        event.type = Event::EventType::KEYDOWN;
        return true;
    }
    return false;
}

void CacaGraphic::loadCanvas(std::shared_ptr<ICanvas>& canvas)
{
    canvas = std::make_shared<CacaCanvas>(this);
}

void CacaGraphic::unloadCanvas(std::shared_ptr<ICanvas>& canvas)
{
    canvas.reset();
}

void CacaGraphic::destroy() { caca_free_display(_display); }

void CacaGraphic::registerSprite(game::ISprite& sprite [[maybe_unused]])
{
    return;
}

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
