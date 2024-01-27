#ifndef COLOR_H
#define COLOR_H

#include <type_traits>

#include "QColor"

enum class Color
{
    NONE,
    RED,
    GREEN,
    BLUE,
    BLACK,
    WHITE,
    YELLOW,

    COUNT // value to know how many constants there are in the enum
          // when counting start at 0
};

constexpr QColor colorToQColor(const Color& color) noexcept
{
    switch (color) {
        case Color::RED:
            return Qt::red;
        case Color::GREEN:
            return Qt::green;
        case Color::BLUE:
            return Qt::blue;
        case Color::BLACK:
            return Qt::black;
        case Color::WHITE:
            return Qt::white;
        case Color::YELLOW:
            return Qt::yellow;
        case Color::NONE:
        case Color::COUNT:
        default:
            return Qt::transparent;
    }
}

constexpr Color& operator++ (Color& color) noexcept
{
    using NumericColorType = std::underlying_type_t<Color>; // get the numeric type that implements that enum
    // casts can be done from numeric type to enum and back
    const auto colorValue = static_cast<NumericColorType>(color);
    const auto count = static_cast<NumericColorType>(Color::COUNT);
    color = static_cast<Color>((colorValue + 1) % count);
    return color;
}

constexpr Color operator++ (Color& color, int) noexcept
{
    auto copy = color;
    ++color;
    return copy;
}

#endif // COLOR_H
