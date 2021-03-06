/**
 * @version 0.1
 * @date 2022-03-09
 */

#pragma once

#include "./ColorCode.hpp"

namespace arc {

/**
 * @brief Common - The color interface.
 * @details This interface is used to represent a color in a palette.
 */
class IColor {
public:
    virtual ~IColor() = default;

    /**
     * @brief Get the color code.
     *
     * @return ColorCode
     */
    virtual ColorCode getColorCode() const = 0;

    /**
     * @brief Get the symbol to use for rendering the color on non-graphical.
     * @return The symbol to use for rendering the color on non-graphical.
     */
    virtual char getSymbol() const = 0;
};

}  // namespace arc
