#pragma once

#include "Color.hpp"
#include "spc/graphic/IPalette.hpp"
#include <array>
#include <memory>

namespace arc::grph {

class Palette : public IPalette {
 private:
    std::array<std::unique_ptr<Color>, 16> _colors; // 16 colors per palette

 public:
    Palette() = default;
    ~Palette() = default;

    void setColor(int index, char symbol, ColorCode colorCode) override
    {
        _colors[index].reset(new Color(colorCode, symbol));
    }

    const IColor& operator[](int index) const override
    {
        if (_colors[index]) {
            return *_colors[index];
        } else {
            throw std::out_of_range("Color not found");
        }
    }
};

} // namespace arc
