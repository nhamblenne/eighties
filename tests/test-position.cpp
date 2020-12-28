/* =======================================================================
 * test-position.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include <eighties/window.hpp>
#include <eighties/image.hpp>
#include <eighties/color.hpp>
#include <eighties/point.hpp>

int emain(int, char**)
{
    eighties::window win(640, 480);
    eighties::image dino("./dino.png");

    eighties::point old_pos{-1, -1};
    while (win.status() != eighties::window::closed) {
        auto pos = win.current_cursor_position();
        if ((pos != old_pos)
            && (0 <= pos.x && pos.x < 640)
            && (0 <= pos.y && pos.y < 480))
        {
            win.clear();
            win.draw_image(pos.x - dino.width()/2, pos.y - dino.height()/2, dino);
            old_pos = pos;
        }
    }
    return 0;
}
