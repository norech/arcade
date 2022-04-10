#pragma once

#include <ncurses.h>

#include "../common/Graphic.hpp"
#include "spc/common/KeyCode.hpp"
#include "spc/graphic/IGraphic.hpp"
#include <unordered_map>

namespace arc::grph {

class NcursesGraphic : public AGraphic {
 public:
    NcursesGraphic() = default;
    ~NcursesGraphic() = default;

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

 private:
    static std::unordered_map<int, arc::KeyCode> _keyMap;
    WINDOW* _window;

    static bool _hasColorsSet;

    bool _willBeClosed = false;
};

} // namespace arc::grph
