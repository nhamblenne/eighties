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
class event;

/// where everything happens
class window
{
public:
    enum status_type {
        opened, ///< the window is open. Not necessary visible due to other overlapping windows.
        hidden, ///< the window is hidden.
        closed ///< the window has been closed
    };
    /// a window of given width an height
    window(int width, int height);
    window(window&&) noexcept;
    window& operator=(window&&) noexcept;
    /// destroy the window. Note that this wait for the window to be closed by
    /// the user if it wasn't already, so calling close beforehand may be desirable.
    ~window();

    /// wait until the window is closed.
    void wait_for_close() const;

    void resize(int new_width, int new_height); ///< resize the window
    void hide(); ///< hide the window
    void show(); ///< show the window if it was hidden
    void close(); ///< close the window

    void clear(); ///< clear the content
    void draw_circle(int xc, int yc, int r, color); ///< draw a circle
    void draw_line(int xb, int yb, int xe, int ye, color); ///< draw a line
    void draw_point(int x, int y, color); ///< draw a point
    void draw_image(int x, int y, image const&); ///< draw an image

    status_type status() const; ///< gives the status of the window
    point current_cursor_position() const; ///< gives the current position of the mouse

    /// get the next event. If wait is true, wait for one if needed.
    event get_event(bool wait = false);

    /// get the next event. If wait is true, wait for one if needed. For key
    /// events the text is the textual value of the key.
    event get_event(std::string& text, bool wait = false);

    /// get an image with the current content of the window.
    image get_image() const;

private:
    std::unique_ptr<window_impl> m_impl;
};

}

#endif
