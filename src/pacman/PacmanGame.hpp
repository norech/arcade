#pragma once

#include <memory>
#include <vector>

#include "../common/Palette.hpp"
#include "../common/VectorInt.hpp"
#include "spc/game/IGame.hpp"
#include "spc/graphic/ICanvas.hpp"
#include "spc/graphic/IGraphic.hpp"
#include "../common/VectorInt.hpp"


namespace arc::game {

class PacmanGame : public IGame {
 private:
    typedef struct score_s {
       size_t score;
       char name[8];
    } score_t;
    score_t score[3];
    grph::Palette _palette;
    std::shared_ptr<grph::ICanvas> _canvas;
    grph::IGraphic* _graphic;
    IManager* _manager;
    bool _mustLoadAnotherGraphic = false;
    VectorInt _player;
    VectorInt _player_mov;
    VectorInt _Blink;
    std::vector<std::string> _map;
    std::vector<std::string> _mapCpy;
    size_t _score;
    float _timer;
    int _pcCount = 0;


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

    void reset(void);

    void hardReset(void);
    void eat(const VectorInt &vec);
    void printScore();
    void blinky(void);
};

} // namespace arc::grph
