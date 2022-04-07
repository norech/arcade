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
    NONE = 0,
    BASIC = 1,              // basic canvas handling
    DRAW_SPRITES = 1 << 1,  // draw sprites on the screen
};

}  // namespace arc::grph
