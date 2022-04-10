#pragma once

#include <memory>
#include <vector>

#include "../common/Game.hpp"
#include "../common/Palette.hpp"
#include "../common/VectorInt.hpp"
#include "spc/game/IGame.hpp"
#include "spc/graphic/ICanvas.hpp"
#include "spc/graphic/IGraphic.hpp"

namespace arc::game {

class PacmanGame : public AGame {
 private:
    static std::vector<std::string> _map;
    grph::Palette _palette;
    std::shared_ptr<grph::ICanvas> _canvas;
    grph::IGraphic* _graphic;
    IManager* _manager;
    VectorInt _player;
    VectorInt _player_mov;
    VectorInt _Blink;
    std::vector<std::string> _mapCpy;
    size_t _score;
    std::string _playername;
    size_t _highscore;
    float _timer;
    int _pcCount = 0;


 public:
    PacmanGame() = default;
    ~PacmanGame() = default;

    void init() override;

    void update(float dt) override;

    void render() override;

    void loadGraphic(grph::IGraphic* graphic) override;

    void unloadGraphic() override;

    void destroy() override;

    bool getCollide(VectorInt nextPos);

    void reset(void);

    void hardReset(void);
    void eat(const VectorInt &vec);
    void printScore();
    void blinky(void);
};

} // namespace arc::grph
