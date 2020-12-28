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
class image;
class point;

class window
{
public:
    enum status_type { opened, hidden, closed };
    window(int width, int height);
    window(window&&) noexcept;
    window& operator=(window&&) noexcept;
    ~window();

    void wait_for_close() const;

    void resize(int new_width, int new_height);
    void hide();
    void show();
    void close();

    void clear();
    void draw_circle(int xc, int yc, int r, color);
    void draw_line(int xb, int yb, int xe, int ye, color);
    void draw_point(int x, int y, color);
    void draw_image(int x, int y, image const&);

    status_type status() const;
    point current_cursor_position() const;

private:
    std::unique_ptr<window_impl> m_impl;
};

}

#endif
