#pragma once

#include <memory>
#include <ncurses.h>

#include "../common/Palette.hpp"
#include "spc/game/IGame.hpp"
#include "spc/graphic/ICanvas.hpp"
#include "spc/graphic/IGraphic.hpp"

namespace arc::game {

class PacmanGame : public IGame {
 private:
    grph::Palette _palette;
    std::shared_ptr<grph::ICanvas> _canvas;
    std::shared_ptr<grph::IGraphic> _graphic;
    int _playerX = 0;
    int _playerY = 0;
    int _score = 0;

 public:
    PacmanGame() = default;
    ~PacmanGame() = default;

    void init() override;

    void update(float dt) override;

    void render() override;

    void loadGraphic(grph::IGraphic* graphic) override;

    void unloadGraphic() override;

    void destroy() override;
};

} // namespace arc::grph
