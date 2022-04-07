/**
 * @version 0.1
 * @date 2022-03-28
 */

#pragma once

#include <memory>

#include "../common/Event.hpp"
#include "../common/IColor.hpp"
#include "../common/IntRect.hpp"

namespace arc::game {

class ICanvas;

/**
 * @brief Graphic - The sprite interface.
 * @details This interface is used to represent and manage a sprite
 */

class ISprite {
    virtual ~ISprite() = default;

    virtual void init() = 0;

    virtual void destroy() = 0;

    virtual void setRect(const IntRect& rect) = 0;

    virtual void setFallbackColor(const IColor& color) = 0;

    virtual void setTexturePath(const std::string& texturePath) = 0;

    virtual const std::string& getTexturePath() = 0;

    virtual const IntRect& getRect() = 0;

    virtual const IColor& getFallbackColor() = 0;
};

}  // namespace arc::game
