#pragma once

#include "spc/common/IManager.hpp"
#include <vector>

namespace arc::core {

class Manager : IManager {
 private:
    grph::IGraphic* _graphic = nullptr;
    game::IGame* _game = nullptr;
    std::vector<std::string> _graphicPaths
        = { "./lib/arcade_sdl2.so", "./lib/arcade_sfml.so",
              "./lib/arcade_ncurses.so", "./lib/arcade_libcaca.so" };
    int _currentGraphicId = 0;
    bool _mustLoadAnotherGraphic = false;

 public:
    Manager() = default;
    ~Manager() = default;

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
};

}
