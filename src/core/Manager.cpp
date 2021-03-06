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
    _isBackToMenu = false;
    if (_graphic != nullptr) {
        _game->loadGraphic(_graphic);
    }
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
    _isBackToMenu = false;
    if (_graphic != nullptr) {
        _game->loadGraphic(_graphic);
    }
}

void Manager::loadGraphic(const std::string& graphic)
{
    if (_graphic != nullptr) {
        if (_game == nullptr)
            _game->unloadGraphic();
        _graphic->destroy();
    }
    if (_loadedGraphics.find(graphic) != _loadedGraphics.end()) {
        _graphic = _loadedGraphics[graphic];
    } else {
        _graphic = GraphicLoader::load(graphic);
        _loadedGraphics[graphic] = _graphic;
    }
    _graphic->init();
    _isGraphicFromLoader = true;

    if (_game != nullptr) {
        _game->loadGraphic(_graphic);
    }
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
    _graphic = nullptr;
}
game::IGame* Manager::getGame() { return _game; }

grph::IGraphic* Manager::getGraphic() { return _graphic; }

bool Manager::isBackToMenu() const { return _isBackToMenu; }

void Manager::reloadCurrentGraphic()
{
    unloadGraphic();
    loadGraphic(_graphicPaths[_currentGraphicId]);
}

std::string Manager::getGraphicPath() const
{
    return _graphicPaths[_currentGraphicId];
}

void Manager::setGraphic(grph::IGraphic* graphic) { _graphic = graphic; }

void Manager::setGame(game::IGame* game) { _game = game; }

void Manager::init()
{
    listGraphics(_graphicPaths);
    listGames(_gamePaths);
}

void Manager::destroy()
{
    if (_graphic != nullptr) {
        if (_game != nullptr)
            _game->unloadGraphic();
        _graphic->destroy();
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

    for (auto& g : _loadedGraphics) {
        // ugly and i dont like it, but sfml seems to crash on unload anyway
        // thanks an uninitialised value of a pthread_mutex_lock of sfml
        // i really dont know how to fix it
        if (g.first.find("arcade_sfml") != std::string::npos)
            continue;
        GraphicLoader::unload(g.second);
    }
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
    if (_mustLoadAnotherGame) {
        unloadGame();
        int movement = _mustLoadNext ? 1 : -1;

        _mustLoadAnotherGame = false;
        _currentGameId = (_currentGameId + movement) % _gamePaths.size();
        loadGame(_gamePaths[_currentGameId]);
    }
}

bool Manager::pollEvent(Event& input)
{
    bool event = _graphic->pollEvent(input);

    if (event && input.type == Event::QUIT) {
        _graphic->close();
        return false;
    }
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
        if (input.keyboardInput.keyCode == KeyCode::L) {
            _mustLoadAnotherGame = true;
            _mustLoadNext = false;
            return false;
        }
        if (input.keyboardInput.keyCode == KeyCode::M) {
            _mustLoadAnotherGame = true;
            _mustLoadNext = true;
            return false;
        }
        if (input.keyboardInput.keyCode == KeyCode::K) {
            this->_graphic->close();
        }
        if (input.keyboardInput.keyCode == KeyCode::I) {
            _isBackToMenu = true;
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
        std::filesystem::create_directory("./highscore");
    }
    std::ifstream read("./highscore/" + gameName + ".txt");
    std::ofstream write("./highscore/" + gameName + "_2.txt");
    if (!read.is_open()) {
        std::ofstream writefile("./highscore/" + gameName + ".txt");
        if (writefile.is_open()) {
            writefile.close();
        }
        read.open("./highscore/" + gameName + ".txt");
    }
    if (!read.is_open()) {
        return;
    }
    if (!write.is_open()) {
        return;
    }
    bool isHighScoreWritten = false;
    std::string line;
    while (std::getline(read, line)) {
        std::stringstream ss(line);
        std::string name;
        std::getline(ss, name, ':');
        if (name == getPlayerName()) {
            write << name << ":" << score << std::endl;
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
