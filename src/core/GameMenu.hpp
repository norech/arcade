#pragma once

#include <memory>
#include <vector>

#include "../common/Game.hpp"
#include "../common/Palette.hpp"
#include "../common/VectorInt.hpp"
#include "Manager.hpp"
#include "spc/game/IGame.hpp"
#include "spc/graphic/ICanvas.hpp"
#include "spc/graphic/IGraphic.hpp"

namespace arc::game {

class GameMenu : public AGame {
 private:
    grph::Palette _palette;
    std::shared_ptr<grph::ICanvas> _canvas;
    grph::IGraphic* _graphic = nullptr;
    int _gameIndex = 0;
    int _graphicIndex = 0;
    bool gameSelected = false;
    bool _showNameInput = false;
    std::vector<std::string> _games;
    std::vector<std::string> _graphics;
    std::vector<std::string> _gamesNames;
    std::vector<std::string> _graphicsNames;
    std::string _name = "player";
    bool _hasSelectedGame = false;
    bool _hasValidatedInput = false;
    bool _focusOnName = false;
    std::vector<arc::core::Score> _scores;

 public:
    GameMenu() = default;
    ~GameMenu() = default;

    void init() override;

    void update(float dt) override;

    void render() override;

    void loadGraphic(grph::IGraphic* graphic) override;

    void unloadGraphic() override;

    void destroy() override;

    const std::string getSelectedGamePath() const;

    const std::string getSelectedGraphicPath() const;

    bool hasSelectedGame() const;

    const IColor& getGameTextColor(int index);

    const IColor& getGraphicTextColor(int index);

    std::string getPlayerName();

    void renderBoxes();
};

} // namespace arc::grph
