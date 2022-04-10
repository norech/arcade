/**
 * @version 0.1
 * @date 2022-04-02
 */

#pragma once

#include "../game/IGame.hpp"
#include "../graphic/IGraphic.hpp"

namespace arc {

class IManager {
public:
    virtual ~IManager() = default;

    /**
     * @brief Loads the specified graphical library from its path.
     */
    virtual void loadGame(const std::string& gamePath) = 0;

    /**
     * @brief Loads the specified game from its path.
     */
    virtual void loadGraphic(const std::string& graphicPath) = 0;

    /**
     * @brief Gets the IGraphic
     */
    virtual grph::IGraphic* getGraphic() = 0;

    /**
     * @brief Gets the IGame
     */
    virtual game::IGame* getGame() = 0;

    /**
     * @brief Sets the IGraphic
     */
    virtual void setGraphic(grph::IGraphic* graphic) = 0;

    /**
     * @brief Sets the IGame
     */
    virtual void setGame(game::IGame* game) = 0;

    /**
     * @brief Saves the high score for the specified identifier.
     */
    virtual void setHighScore(const std::string& scoreIdentifier,
                              long score) = 0;

    /**
     * @brief Gets the high score for the specified identifier
     */
    virtual long getHighScore(const std::string& scoreIdentifier) = 0;

    /**
     * @brief Sets the player name
     */
    virtual void setPlayerName(const std::string& playerName) = 0;

    /**
     * @brief Gets the player name
     */
    virtual std::string getPlayerName(void) = 0;

    /**
     * @brief Init the game and the graphic, and then load the graphic lib into
     * the game
     */
    virtual void init() = 0;

    /**
     * @brief Unloads the graphic lib from the game, and then destroy both
     */
    virtual void destroy() = 0;

    /**
     * @brief Checks if the manager can update the game and the graphical lib
     */
    virtual bool canUpdate() = 0;

    /**
     * @brief Updates the game, handle the events and draw on the graphic lib
     */
    virtual void update() = 0;

    /**
     * @brief Polls the events from the graphic library and handle the system
     * events, or return them if they are game events.
     * @param input An event to fill.
     *
     * @return true An input was found since the last call to this method.
     * @return false No input was found since the last call to this method.
     */
    virtual bool pollEvent(Event& input) = 0;
};

}  // namespace arc
