//
// EPITECH PROJECT, 2022
// arcade
// File description:
// graphic
//

#pragma once
#include "spc/graphic/IGraphic.hpp"

namespace arc::grph {

class AGraphic : public IGraphic {
 public:
    AGraphic() = default;
    ~AGraphic() = default;

    void init() override { }
    void close() override { }
    void clear() override { }
    void render() override { }

    float tick() override { return (0); }
    bool pollEvent(Event& input [[maybe_unused]]) override { return (false); }
    bool isOpen() override { return (false); }

    void loadCanvas(std::shared_ptr<ICanvas>& canvas [[maybe_unused]]) override
    {
    }

    void unloadCanvas(
        std::shared_ptr<ICanvas>& canvas [[maybe_unused]]) override
    {
    }

    void destroy() override { }

    void registerSprite(game::ISprite& sprite [[maybe_unused]]) override { }
};
}
