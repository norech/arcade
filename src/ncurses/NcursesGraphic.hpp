#pragma once

#include <ncurses.h>

#include "spc/graphic/IGraphic.hpp"

namespace arc::grph {

class NcursesGraphic : public IGraphic {
 public:
    void init() override;

    bool isOpen() override;

    void close() override;

    void render() override;

    float tick() override;

    bool pollEvent(Event& input) override;

    void loadCanvas(std::shared_ptr<ICanvas>& canvas) override;

    void unloadCanvas(std::shared_ptr<ICanvas>& canvas) override;

    void destroy() override;
};

} // namespace arc::grph
