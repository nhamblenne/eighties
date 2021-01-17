/* =======================================================================
 * mandelbrot.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/window.hpp"
#include <eighties/color.hpp>

#include <complex>
#include <thread>

constexpr auto win_size = 800;

void mandelbrot(double xmin, double ymin, double xmax, double ymax)
{
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
                win.draw_point(j, i,
                               eighties::color(c / 16 / 16 * 16,
                                               c / 16 % 16 * 16,
                                               c % 16 * 16));
        }
    }
}

void alt_mandelbrot(double xmin, double ymin, double xmax, double ymax)
{
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
    eighties::window win(win_size, win_size);
    for (int i = 0; i < win_size; ++i) {
        double y0 = ymin + i*dy;
        int cur_c = -1;
        int cur_p = -1;
        for (int j = 0; j < win_size; ++j) {
            int c;
            auto z0 = std::complex(xmin + j * dx, y0);
            auto z = z0;
            for (c = 0; c < 16 * 16 * 16 && norm(z) <= 4.0; ++c) {
                z = z * z + z0;
            }
            if (j == 0) {
                cur_c = c;
                cur_p = j;
            } else if (c != cur_c) {
                if (cur_c == 0)
                    win.draw_line(cur_p, i, j - 1, i,
                                  eighties::color::white);
                else
                    win.draw_line(cur_p, i, j - 1, i,
                                  eighties::color(cur_c % 16 * 16,
                                                  cur_c / 16 % 16 * 16,
                                                  cur_c / 16 / 16 * 16));
                cur_c = c;
                cur_p = j;
            }
        }
        if (cur_c == 0)
            win.draw_line(cur_p, i, win_size - 1, i,
                          eighties::color::white);
        else
            win.draw_line(cur_p, i, win_size - 1, i,
                          eighties::color(cur_c % 16 * 16,
                                          cur_c / 16 % 16 * 16,
                                          cur_c / 16 / 16 * 16));
    }
}

int emain(int, char*[])
{
    std::thread t1(mandelbrot, -2.0, -2.0, 2.0, 2.0);
    std::thread t2(mandelbrot, -2.0, -1.0, 0.0, 1.0);
    std::thread t3(alt_mandelbrot, -2.0, -1.0, 0.0, 1.0);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
