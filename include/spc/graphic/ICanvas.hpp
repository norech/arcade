/**
 * @version 0.1
 * @date 2022-03-09
 */
#pragma once

#include "../common/IColor.hpp"
#include "../game/ISprite.hpp"
#include "./CanvasCapacity.hpp"

namespace arc::grph {

/**
 * @brief Graphic - The canvas interface.
 * @details This interface is used to represent a canvas,
 * where basic shapes can be drawn.
 */
class ICanvas {
public:
    virtual ~ICanvas() = default;

    /**
     * @brief Get the Capacities object
     *
     * @return CanvasCapacity bit field
     * @example BASIC | DRAW_POINT | DRAW_TEXT
     */
    virtual CanvasCapacity getCapacities() const = 0;

    /**
     * @brief Start the drawing of the canvas.
     */
    virtual void startDraw() = 0;

    /**
     * @brief Stop the drawing of the canvas.
     */
    virtual void endDraw() = 0;

    /**
     * Draws a point on the canvas.
     * A point may represent a single pixel or any other single unit in a
     * grid.
     */
    virtual void drawPoint(int x, int y, const IColor& color) = 0;

    /**
     * Draws a text on the canvas.
     * A text may represent one or more characters, and the position must*
     * be aligned to the nearest point on the grid.
     */
    virtual void drawText(int x, int y, const std::string& text,
                          const IColor& foreColor) = 0;

    /**
     * Draws a sprite on the canvas.
     * A sprite may represent a single image, or use the fallback color if
     * sprites are not supported.
     */
    virtual void drawSprite(const game::ISprite& sprite) = 0;
};

}  // namespace arc::grph
