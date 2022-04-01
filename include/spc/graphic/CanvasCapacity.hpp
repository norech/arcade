/**
 * @version 0.1
 * @date 2022-03-27
 */

#pragma once

namespace arc::grph {

/**
 * @brief Graphic - The capacity of the canvas
 */
enum CanvasCapacity {
    BASIC = 1,             // basic canvas handling
    DRAW_POINT = 1 << 1,   // draw points on the screen
    DRAW_TEXT = 1 << 2,    // draw text on the screen
    DRAW_SPRITE = 1 << 3,  // draw a sprite with images on the screen
    NONE = 0
};

}  // namespace arc::grph
