/**
 * @version 0.1
 * @date 2022-03-09
 */

#pragma once

#include "../common/ColorCode.hpp"

namespace arc {
class IColor;
}

namespace arc::grph {

/**
 * @brief Graphic - The palette interface.
 * @details This interface is used to represent a palette,
 * containing colors to draw.
 */
class IPalette {
public:
    virtual ~IPalette() = default;

    /**
     * Set the color for the specified index.
     * @param index The index of the color to set.
     * @param symbol The symbol to use for rendering the color on non-graphical.
     * @param color The color to set.
     */
    virtual void setColor(int index, char symbol, ColorCode colorCode) = 0;

    /*
     * @brief Get the color for the specified index.
     * @param index The index of the color to get.
     * @return The color for the specified index.
     */
    virtual const IColor& operator[](int index) const = 0;
};

}  // namespace arc::grph
