/* =======================================================================
 * mandelbrot.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/window.hpp"
#include <eighties/color.hpp>

#include <complex>
#include <iostream>

int emain(int, char*[])
{
    constexpr auto win_size = 800;
    auto xmin = -2.0;
    auto xmax =  2.0;
    auto ymin = -2.0;
    auto ymax =  2.0;
    auto dx = (xmax-xmin) / (win_size-1);
    auto dy = (ymax-ymin) / (win_size-1);
    if (dx < dy) {
        auto yc = (ymin+ymax) / 2.0;
        dy = dx;
        ymin = yc - dy * (win_size-1) / 2.0;
        ymax = yc + dy * (win_size-1) / 2.0;
    } else {
        auto xc = (xmin+xmax) / 2;
        dx = dy;
        xmin = xc - dx * (win_size-1) / 2.0;
        xmax = xc + dx * (win_size-1) / 2.0;
    }
    std::cout << xmin << ":" << ymin << " " << xmax << ":" << ymax << '\n';
    eighties::window win(win_size, win_size);
    for (int i = 0; i < win_size; ++i) {
        double y0 = ymin + i*dy;
        for (int j = 0; j < win_size; ++j) {
            int c;
            auto z0 = std::complex(xmin + j*dx, y0);
            auto z = z0;
            for (c = 0; c < 16*16*16 && norm(z) <= 4.0; ++c) {
                z = z*z + z0;
            }
            if (c == 0)
                win.draw_point(j, i, eighties::color::white);
            else
                win.draw_point(j, i, eighties::color(c / 16 / 16 * 16,
                                                     c / 16 % 16 * 16,
                                                     c % 16 * 16));
        }
    }
    win.wait_for_close();
    return 0;
}
