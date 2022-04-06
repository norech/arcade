#pragma once

#include <ncurses.h>

#include "../common/graphic.hpp"
#include "spc/graphic/IGraphic.hpp"

namespace arc::grph {

class NcursesGraphic : public Graphic {
 public:
    NcursesGraphic();
    ~NcursesGraphic();

    void init() override;

    bool isOpen() override;

    void close() override;

    void render() override;

    float tick() override;

    void clear() override;

    bool pollEvent(Event& input) override;

    void loadCanvas(std::shared_ptr<ICanvas>& canvas) override;

    void unloadCanvas(std::shared_ptr<ICanvas>& canvas) override;

    void destroy() override;

    int getColorIndex(const ColorCode& color);

    void registerSprite(game::ISprite& sprite);

    WINDOW* _window;

    static bool _hasColorsSet;
};

} // namespace arc::grph
