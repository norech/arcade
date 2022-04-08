#pragma once

#include "spc/common/IManager.hpp"
#include "spc/graphic/IGraphic.hpp"
#include <map>
#include <vector>

namespace arc::core {

class Manager : IManager {
 private:
    grph::IGraphic* _graphic = nullptr;
    game::IGame* _game = nullptr;
    std::vector<std::string> _graphicPaths;
    std::map<std::string, grph::IGraphic*> _loadedGraphics = {};
    int _currentGraphicId = 0;
    bool _mustLoadAnotherGraphic = false;
    bool _isGameFromLoader = false;
    bool _isGraphicFromLoader = false;

 public:
    Manager() = default;
    ~Manager() = default;

    void loadGame(arc::game::IGame* game);
    void unloadGame();
    void unloadGraphic();
    void loadGame(const std::string& gamePath) override;
    void loadGraphic(const std::string& graphicPath) override;
    grph::IGraphic* getGraphic() override;
    game::IGame* getGame() override;
    void setGraphic(grph::IGraphic* graphic) override;
    void setGame(game::IGame* game) override;
    void init() override;
    void destroy() override;
    bool canUpdate() override;
    void update() override;
    bool pollEvent(Event& input) override;
    void listGames(std::vector<std::string>& games);
    void listGraphics(std::vector<std::string>& graphics);
};

}
