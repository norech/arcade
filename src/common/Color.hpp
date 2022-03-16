#pragma once

#include "spc/common/IColor.hpp"

namespace arc {

class Color : public IColor {
 private:
    ColorCode _code;
    char symbol;

 public:
    Color(ColorCode code, char symbol)
        : _code(code)
        , symbol(symbol)
    {
    }
    ~Color() = default;

    ColorCode getColorCode() const override { return _code; }

    char getSymbol() const override { return symbol; }
};

} // namespace arc
