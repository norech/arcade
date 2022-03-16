/**
 * @version 0.1
 * @date 2022-03-08
 */

#pragma once

#include <memory>

#include "../common/Event.hpp"
#include "./ICanvas.hpp"

namespace arc::grph {

/**
 * @brief Graphic - The graphical library interface.
 * @details This interface is used to represent and manage a display and its
 * events.
 */

class IGraphic {
public:
    virtual ~IGraphic() = default;

    /**
     * @brief Initialize the graphical library.
     */
    virtual void init() = 0;

    /**
     * @brief Is the window opened?
     */
    virtual bool isOpen() = 0;

    /**
     * Triggers any last operations and marks the window as closed.
     * The next call to `isOpen` will return `false`.
     *
     * @brief Close the window.
     */
    virtual void close() = 0;

    /**
     * Render the screen buffer on the screen.
     */
    virtual void render() = 0;

    /**
     * Returns the amount of time since the last call to `tick`.
     */
    virtual float tick() = 0;

    /**
     * @brief Polls the events.
     * @param input An event to fill.
     *
     * @return true An input was found since the last call to this method.
     * The input is then available in the `getLastInput` method.
     * @return false No input was found since the last call to this method.
     */
    virtual bool pollEvent(Event &input) = 0;

    /**
     * @brief Loads the canvas.
     * Is a modifiable shared pointer to the canvas.
     * @note May be implemented by assigning the canvas argument to a
     * canvas matching the current graphical library.
     */
    virtual void loadCanvas(std::shared_ptr<ICanvas> &canvas) = 0;

    /**
     * @brief Unloads the canvas.
     * Is a modifiable shared pointer to the canvas.
     */
    virtual void unloadCanvas(std::shared_ptr<ICanvas> &canvas) = 0;

    /**
     * @brief Destroy the graphical library.
     */
    virtual void destroy() = 0;
};

}  // namespace arc::grph
