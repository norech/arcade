#pragma once

#include <memory>
#include <ncurses.h>

#include "../common/Palette.hpp"
#include "spc/game/IGame.hpp"
#include "spc/graphic/ICanvas.hpp"
#include "spc/graphic/IGraphic.hpp"
#include "../common/VectorInt.hpp"
#include "vector"

namespace arc::game {

class PacmanGame : public IGame {
 private:
    grph::Palette _palette;
    std::shared_ptr<grph::ICanvas> _canvas;
    grph::IGraphic* _graphic;
    bool _mustLoadAnotherGraphic = false;
    VectorInt _player;
    VectorInt _player_mov;
    int _score = 0;
    VectorInt _Blink;
    std::vector<std::string> _map;
    float _timer;

 public:
    PacmanGame() = default;
    ~PacmanGame() = default;

    void init() override;

    void update(float dt) override;

    void render() override;

    void loadGraphic(grph::IGraphic* graphic) override;

    bool mustLoadAnotherGraphic() const override;

    void unloadGraphic() override;

    void destroy() override;
    bool getCollide(VectorInt nextPos);

};

} // namespace arc::grph
