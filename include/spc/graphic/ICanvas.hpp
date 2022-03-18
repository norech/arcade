/**
 * @version 0.1
 * @date 2022-03-09
 */
#pragma once

#include "../common/IColor.hpp"

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
};

}  // namespace arc::grph
