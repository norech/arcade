#pragma once

#include <memory>
#include <vector>

#include "../common/Palette.hpp"
#include "../common/VectorInt.hpp"
#include "spc/game/IGame.hpp"
#include "spc/graphic/ICanvas.hpp"
#include "spc/graphic/IGraphic.hpp"

namespace arc::game {

class GameMenu : public IGame {
 private:
    grph::Palette _palette;
    std::shared_ptr<grph::ICanvas> _canvas;
    grph::IGraphic* _graphic;
    IManager* _manager;
    int _gameIndex = 0;
    int _graphicIndex = 0;
    bool _hasSelectedGame = false;

 public:
    GameMenu() = default;
    ~GameMenu() = default;

    void init() override;

    void update(float dt) override;

    void render() override;

    void loadGraphic(grph::IGraphic* graphic) override;

    bool mustLoadAnotherGraphic() const override;

    void unloadGraphic() override;

    void setManager(IManager* manager) override;

    void destroy() override;

    const std::string getSelectedGamePath() const;

    const std::string getSelectedGraphicPath() const;

    bool hasSelectedGame() const;
};

} // namespace arc::grph
