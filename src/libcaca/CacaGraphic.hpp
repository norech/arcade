#pragma once

#include <caca.h>

#include <ncurses.h>

#include "../common/Graphic.hpp"
#include "spc/common/KeyCode.hpp"
#include "spc/graphic/IGraphic.hpp"
#include <unordered_map>

namespace arc::grph {

class CacaGraphic : public AGraphic {
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
    static std::unordered_map<int, KeyCode> _keyMap;
};
}
