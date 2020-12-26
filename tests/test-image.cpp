/* =======================================================================
 * test-image.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/window.hpp"
#include <eighties/image.hpp>

#include <unistd.h>
#include <eighties/color.hpp>

int emain(int, char**)
{
    eighties::window win(640, 480);
    eighties::image dino("./dino.png");

    for (int i = 20; i <= 500; i += 20) {
        win.clear();
        win.draw_line(20, 20, 500, 20, eighties::color::red);
        win.draw_line(20, 40, 500, 40, eighties::color::red);
        win.draw_line(20, 60, 500, 60, eighties::color::red);
        win.draw_line(20, 80, 500, 80, eighties::color::red);
        win.draw_image(i, 20, dino);
        sleep(1);
    }

    win.draw_image(200, 200, dino);
    win.draw_line(199, 199, 199+dino.width()+1, 199, eighties::color::red);
    win.draw_line(199, 199, 199, 199+dino.height()+1, eighties::color::red);
    win.draw_line(199, 199+dino.height()+1, 199+dino.width()+1, 199+dino.height()+1, eighties::color::red);
    win.draw_line(199+dino.width()+1, 199,  199+dino.width()+1, 199+dino.height()+1, eighties::color::red);

    win.wait_for_close();
    return 0;
}
