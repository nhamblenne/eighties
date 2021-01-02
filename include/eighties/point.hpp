#ifndef EIGHTIES_POINT_HPP
#define EIGHTIES_POINT_HPP

/* =======================================================================
 * point.hpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

namespace eighties {

/// describe a position
class point
{
public:
    point() = default;

    constexpr point(int px, int py)
        : x(px), y(py)
    {}

    int x;
    int y;
};

/// compare two points for equality
constexpr bool operator==(point l, point r)
{
    return l.x == r.x && l.y == r.y;
}

/// compare two points for inequality
constexpr bool operator!=(point l, point r)
{
    return !(l == r);
}

}

#endif
