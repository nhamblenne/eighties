#ifndef EIGHTIES_WINDOW_HPP
#define EIGHTIES_WINDOW_HPP

/* =======================================================================
 * window.hpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include <memory>

namespace eighties {

class window_impl;
class color;

class window
{
public:
    window(int width, int height);
    window(window&&) noexcept;
    window& operator=(window&&) noexcept;
    ~window();

    void wait_for_close() const;

    void resize(int new_width, int new_height);

    void clear();
    void circle(int xc, int yc, int r, color);
    void draw_line(int xb, int yb, int xe, int ye, color);
    void plot(int x, int y, color);

private:
    std::unique_ptr<window_impl> m_impl;
};

}

#endif
