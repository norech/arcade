#pragma once

#include <memory>
#include <vector>

#include "../common/Palette.hpp"
#include "../common/Game.hpp"
#include "spc/game/IGame.hpp"
#include "spc/graphic/ICanvas.hpp"
#include "spc/graphic/IGraphic.hpp"
#include "../common/VectorInt.hpp"


namespace arc::game {

class PacmanGame : public AGame {
 private:
    grph::Palette _palette;
    std::shared_ptr<grph::ICanvas> _canvas;
    grph::IGraphic* _graphic;
    IManager* _manager;
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

    void setManager(IManager *manager) override;

    void destroy() override;

    bool getCollide(VectorInt nextPos);
};

} // namespace arc::grph
