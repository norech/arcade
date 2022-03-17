#pragma once

#include <ncurses.h>

#include "spc/graphic/IGraphic.hpp"
#include "../common/graphic.hpp"

namespace arc::grph {

class NcursesGraphic : public Graphic {
 public:

    NcursesGraphic(std::string &name, int x, int y);
    ~NcursesGraphic();

    void init() override;

    bool isOpen() override;

    void close() override;

    void render() override;

    float tick() override;

    bool pollEvent(Event& input) override;

    void loadCanvas(std::shared_ptr<ICanvas>& canvas) override;

    void unloadCanvas(std::shared_ptr<ICanvas>& canvas) override;

    void clear() override;

    void destroy() override;

    WINDOW *_window;
};

} // namespace arc::grph
