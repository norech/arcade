#include "./Manager.hpp"
#include "./Loader.hpp"
#include "./ManagerError.hpp"
#include "spc/common/KeyCode.hpp"
#include <filesystem>
#include <fstream>

namespace arc::core {

using GraphicLoader = arc::core::Loader<DLType::GRAPHICAL, grph::IGraphic>;
using GameLoader = arc::core::Loader<DLType::GAME, game::IGame>;

void Manager::loadGame(arc::game::IGame* game)
{
    if (_game != nullptr) {
        throw ManagerError("Game already loaded");
    }
    if (game == nullptr) {
        throw ManagerError("Game is null");
    }
    _game = game;
    _game->setManager(this);
    game->init();
    _isGameFromLoader = false;
}

void Manager::loadGame(const std::string& game)
{
    if (_game != nullptr) {
        throw ManagerError("Game already loaded");
    }
    _game = GameLoader::load(game);
    _game->setManager(this);
    _game->init();
    _isGameFromLoader = true;
}

void Manager::loadGraphic(const std::string& graphic)
{
    if (_game == nullptr)
        throw ManagerError("Game not yet loaded!");

    if (_graphic != nullptr) {
        _game->unloadGraphic();
        _graphic->destroy();
        GraphicLoader::unload(_graphic);
    }
    _graphic = GraphicLoader::load(graphic);
    _graphic->init();
    _isGraphicFromLoader = true;

    _game->loadGraphic(_graphic);
}

void Manager::unloadGame()
{
    if (_game == nullptr)
        throw ManagerError("Game not yet loaded!");
    if (_graphic != nullptr)
        _game->unloadGraphic();
    _game->destroy();
    if (_isGameFromLoader) {
        GameLoader::unload(_game);
    }
    _game = nullptr;
}

void Manager::unloadGraphic()
{
    if (_graphic == nullptr)
        throw ManagerError("Graphic not yet loaded!");
    if (_game != nullptr)
        _game->unloadGraphic();
    _graphic->destroy();
    if (_isGraphicFromLoader) {
        GraphicLoader::unload(_graphic);
    }
    _graphic = nullptr;
}
game::IGame* Manager::getGame() { return _game; }

grph::IGraphic* Manager::getGraphic() { return _graphic; }

void Manager::setGraphic(grph::IGraphic* graphic) { _graphic = graphic; }

void Manager::setGame(game::IGame* game) { _game = game; }

void Manager::init() { listGraphics(_graphicPaths); }

void Manager::destroy()
{
    if (_graphic != nullptr) {
        _game->unloadGraphic();
        _graphic->destroy();
        if (_isGraphicFromLoader) {
            GraphicLoader::unload(_graphic);
        }
    }
    if (_game != nullptr) {
        _game->destroy();
        if (_isGameFromLoader) {
            GameLoader::unload(_game);
        }
    }
    _isGraphicFromLoader = false;
    _isGameFromLoader = false;
    _game = nullptr;
    _graphic = nullptr;
}

bool Manager::canUpdate() { return _graphic->isOpen(); }

void Manager::update()
{
    if (_game == nullptr) {
        throw ManagerError("No game loaded");
    }
    if (_graphic == nullptr) {
        throw ManagerError("No graphic loaded");
    }
    _game->update(_graphic->tick());
    _game->render();
    if (_mustLoadAnotherGraphic) {
        unloadGraphic();
        int movement = _mustLoadNext ? 1 : -1;

        _mustLoadAnotherGraphic = false;
        _currentGraphicId
            = (_currentGraphicId + movement) % _graphicPaths.size();
        loadGraphic(_graphicPaths[_currentGraphicId]);
    }
}

bool Manager::pollEvent(Event& input)
{
    bool event = _graphic->pollEvent(input);
    if (event && input.type == Event::KEYDOWN) {
        if (input.keyboardInput.keyCode == KeyCode::O) {
            _mustLoadAnotherGraphic = true;
            _mustLoadNext = false;
            return false;
        }
        if (input.keyboardInput.keyCode == KeyCode::P) {
            _mustLoadAnotherGraphic = true;
            _mustLoadNext = true;
            return false;
        }
        if (input.keyboardInput.keyCode == KeyCode::K) {
            this->_graphic->close();
        }
    }
    return event;
}

void Manager::listGames(std::vector<std::string>& games)
{
    games.clear();
    for (auto& lib : std::filesystem::directory_iterator("./lib")) {
        if (GameLoader::isLoadable(lib.path()))
            games.push_back(lib.path());
    }
    if (games.size() == 0)
        throw ManagerError("No games has been found in ./lib");
}

void Manager::listGraphics(std::vector<std::string>& graphics)
{
    graphics.clear();
    for (auto& lib : std::filesystem::directory_iterator("./lib")) {
        if (GraphicLoader::isLoadable(lib.path()))
            graphics.push_back(lib.path());
    }
    if (graphics.size() == 0)
        throw ManagerError("No graphic library has been found in ./lib");
}

std::string Manager::getPlayerName() { return _playerName; }

void Manager::setPlayerName(const std::string& name) { _playerName = name; }

void Manager::setHighScore(const std::string& gameName, long score)
{
    if (!std::filesystem::is_directory("./highscore")
        || !std::filesystem::exists("./highscore")) {
        return;
    }
    std::ifstream read("./highscore/" + gameName + ".txt");
    std::ofstream write("./highscore/" + gameName + "_2.txt");
    if (!read.is_open()) {
        return;
    }
    if (!write.is_open()) {
        return;
    }
    bool isHighScoreWritten = false;
    std::string line;
    long lineScore;
    while (std::getline(read, line)) {
        std::stringstream ss(line);
        std::string name;
        std::getline(ss, name, ':');
        ss >> lineScore;
        if (name == getPlayerName()) {
            write << name << ":" << lineScore << std::endl;
            isHighScoreWritten = true;
        } else {
            write << line << std::endl;
        }
    }
    if (!isHighScoreWritten) {
        write << getPlayerName() << ":" << score << std::endl;
    }
    read.close();
    write.close();
    std::filesystem::remove("./highscore/" + gameName + ".txt");
    std::filesystem::rename("./highscore/" + gameName + "_2.txt",
        "./highscore/" + gameName + ".txt");
}

long Manager::getHighScore(const std::string& gameName)
{
    if (!std::filesystem::is_directory("./highscore")
        || !std::filesystem::exists("./highscore")) {
        return 0;
    }
    std::fstream file("./highscore/" + gameName + ".txt");
    if (!file.is_open()) {
        return 0;
    }
    std::string line;
    long score = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        std::getline(ss, name, ':');
        if (name == getPlayerName()) {
            ss >> score;
            file.close();
            return score;
        }
    }
    file.close();
    return 0;
}

std::unordered_map<std::string, long> Manager::getAllHighScores(
    const std::string& gameName)
{
    std::unordered_map<std::string, long> scores;
    if (!std::filesystem::is_directory("./highscore")
        || !std::filesystem::exists("./highscore")) {
        return scores;
    }
    std::ifstream file("./highscore/" + gameName + ".txt");
    if (!file.is_open()) {
        return scores;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        long score;
        std::getline(ss, name, ':');
        ss >> score;
        scores[name] = score;
    }
    return scores;
}

std::vector<Score> Manager::getAllHighScores()
{
    std::vector<Score> scores;
    if (!std::filesystem::is_directory("./highscore")
        || !std::filesystem::exists("./highscore")) {
        return scores;
    }
    for (auto& file : std::filesystem::directory_iterator("./highscore")) {
        for (auto& score : getAllHighScores(file.path().stem().string())) {
            Score s
                = { score.first, file.path().stem().string(), score.second };
            scores.emplace_back(s);
        }
    }
    std::sort(scores.begin(), scores.end(),
        [](const Score& a, const Score& b) { return a.score > b.score; });
    return scores;
}

} // namespace arc::core
