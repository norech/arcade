#pragma once

#include "spc/common/IManager.hpp"
#include <unordered_map>
#include <vector>

namespace arc::core {

struct Score {
    std::string name;
    std::string game;
    long score;
};

class Manager : IManager {
 private:
    grph::IGraphic* _graphic = nullptr;
    game::IGame* _game = nullptr;
    std::vector<std::string> _graphicPaths;
    int _currentGraphicId = 0;
    bool _mustLoadAnotherGraphic = false;
    bool _mustLoadNext = false;
    bool _isGameFromLoader = false;
    bool _isGraphicFromLoader = false;
    std::string _playerName;

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
    std::string getPlayerName() override;
    void setPlayerName(const std::string& name) override;
    void setHighScore(const std::string& gameName, long score) override;
    long getHighScore(const std::string& gameName) override;
    std::unordered_map<std::string, long> getAllHighScores(
        const std::string& gameName);
    std::vector<Score> getAllHighScores();
};
}
