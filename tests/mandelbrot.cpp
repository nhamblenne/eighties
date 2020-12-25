/* =======================================================================
 * mandelbrot.cpp.c
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/window.hpp"
#include <eighties/color.hpp>

#include <complex>

int emain(int, char*[])
{
    eighties::window win(800, 600);
    for (int i = 0; i < 600; ++i) {
        double y0 = -2.0 + i/150.0;
        for (int j = 0; j < 800; ++j) {
            auto z0 = std::complex(-2.0 + (j-100)/150.0, y0);
            int c;
            auto z = z0;
            for (c = 0; c < 16*16*16 && norm(z) <= 4.0; ++c) {
                z = z*z + z0;
            }
            if (c == 0)
                win.plot(j, i, eighties::color::white);
            else
                win.plot(j, i, eighties::color(c/16/16*16, c/16%16*16, c%16*16));
        }
    }
    win.wait_for_close();
    return 0;
}
