#ifndef EIGHTIES_COLOR_HPP
#define EIGHTIES_COLOR_HPP

/* =======================================================================
 * color.hpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include <stdint.h>

namespace eighties {

/// describe a color in RGBA format.
struct color
{
    constexpr color(uint8_t pr, uint8_t pg, uint8_t pb, uint8_t pa = 255)
        : r(pr), g(pg), b(pb), a(pa)
    {}
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    static color const black;
    static color const blue;
    static color const green;
    static color const cyan;
    static color const red;
    static color const magenta;
    static color const yellow;
    static color const white;
};

inline color const color::black   {   0,   0,   0 };
inline color const color::blue    {   0,   0, 255 };
inline color const color::green   {   0, 255,   0 };
inline color const color::cyan    {   0, 255, 255 };
inline color const color::red     { 255,   0,   0 };
inline color const color::magenta { 255,   0, 255 };
inline color const color::yellow  { 255, 255,   0 };
inline color const color::white   { 255, 255, 255 };

}

#endif
