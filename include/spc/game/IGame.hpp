/**
 * @version 0.1
 * @date 2022-03-08
 */

#pragma once

namespace arc::grph {
class IGraphic;
}

namespace arc::game {

/**
 * @brief Game - The game interface.
 * @details This interface is used to represent a game.
 */
class IGame {
public:
    virtual ~IGame() = default;

    /**
     * Trigger the initialization of the game logic.
     * This method is called once at the beginning of the game.
     *
     * You should call `loadDisplay` before calling this method.
     *
     * @brief Initialize the game.
     * @note Behaviour is undefined if `init` is called when no
     * graphical library is loaded.
     */
    virtual void init() = 0;

    /**
     * It is called every time the game is updated (input trigger, clock update,
     * etc.).
     *
     * @brief Update the game.
     * @param dt Delta time.
     * @note Behaviour is undefined if `update` is called when no
     * graphical library is loaded.
     */
    virtual void update(float dt) = 0;

    /**
     * It is called every frame.
     *
     * @brief Render the game.
     * @note Behaviour is undefined if `render` is called when no
     * graphical library is loaded.
     */
    virtual void render() = 0;

    /**
     * @brief Loads the specified graphical library.
     * @throw std::exception if a display is already loaded.
     * @note It takes a pointer to avoid interface dependency.
     */
    virtual void loadGraphic(grph::IGraphic* graphic) = 0;

    /**
     * @brief Unloads the currently loaded graphical library.
     */
    virtual void unloadGraphic() = 0;

    /**
     * @brief Called each frame, checks if another graphical library should
     * be loaded.
     */
    virtual bool mustLoadAnotherGraphic() const = 0;

    /**
     * Triggers any last operations before the game is destroyed.
     *
     * @brief Destroy the game.
     */
    virtual void destroy() = 0;
};

}  // namespace arc::game
