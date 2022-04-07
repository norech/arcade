#pragma once

#include <caca.h>

#include <ncurses.h>

#include "../common/graphic.hpp"
#include "spc/graphic/IGraphic.hpp"

namespace arc::grph {

class CacaGraphic : public Graphic {
 public:
    CacaGraphic() = default;
    ~CacaGraphic() = default;

    void init() override;

    bool isOpen() override;

    void close() override;

    void render() override;

    float tick() override;

    void clear() override;

    bool pollEvent(Event& Input) override;

    void loadCanvas(std::shared_ptr<ICanvas>& canvas) override;
    void unloadCanvas(std::shared_ptr<ICanvas>& canvas) override;

    void destroy() override;

    void registerSprite(game::ISprite& sprite) override;

    int getColorIndex(const ColorCode& color);
    int getCacaColor(const IColor& color);

    caca_canvas_t* _canvas;
    caca_display_t* _display;
    bool _willBeClosed = false;
};

}
