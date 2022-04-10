/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Sprite
*/

#pragma once
#include "spc/game/ISprite.hpp"

namespace arc::game {

class ASprite : public ISprite {
 public:
    ASprite() = default;
    ~ASprite() = default;

    void init() override;

    void destroy() override;

    void setRect(const IntRect& rect) override;

    void setFallbackColor(const IColor& color) override;

    void setTexturePath(const std::string& texturePath) override;

    const std::string& getTexturePath() override;

    const IntRect& getRect() override;

    const IColor& getFallbackColor() override;
};
}
