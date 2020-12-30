/* =======================================================================
 * mandelbrot.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include <eighties/window.hpp>
#include <eighties/color.hpp>
#include <eighties/image.hpp>
#include <eighties/event.hpp>
#include <eighties/point.hpp>

#include <complex>

int emain(int, char*[])
{
    constexpr auto win_size = 800;
    auto xmin = -2.0;
    auto xmax =  2.0;
    auto ymin = -2.0;
    auto ymax =  2.0;
    eighties::window win(win_size, win_size);
    for (;;) {
        auto dx = (xmax - xmin) / (win_size - 1);
        auto dy = (ymax - ymin) / (win_size - 1);
        if (dx < dy) {
            auto yc = (ymin + ymax) / 2.0;
            dy = dx;
            ymin = yc - dy * (win_size - 1) / 2.0;
            ymax = yc + dy * (win_size - 1) / 2.0;
        } else {
            auto xc = (xmin + xmax) / 2;
            dx = dy;
            xmin = xc - dx * (win_size - 1) / 2.0;
            xmax = xc + dx * (win_size - 1) / 2.0;
        }
        for (int i = 0; i < win_size; ++i) {
            double y0 = ymin + i * dy;
            for (int j = 0; j < win_size; ++j) {
                int c;
                auto z0 = std::complex(xmin + j * dx, y0);
                auto z = z0;
                for (c = 0; c < 16 * 16 * 16 && norm(z) <= 4.0; ++c) {
                    z = z * z + z0;
                }
                if (c == 0)
                    win.draw_point(j, i, eighties::color::white);
                else
                    win.draw_point(j, i, eighties::color(c / 16 / 16 * 16,
                                                         c / 16 % 16 * 16,
                                                         c % 16 * 16));
            }
        }
        auto im = win.get_image();
        bool zooming = false;
        eighties::point pt{-1, -1};
        eighties::point old_pt{-1, -1};
        for (;;) {
            auto ev = win.get_event(!zooming);
            if (ev.type == eighties::event_type::key_down) {
                if (ev.key.key == eighties::key_t::escape) {
                    win.close();
                    return 0;
                }
            }
            if (ev.type == eighties::event_type::button_down) {
                if (zooming) {
                    auto x1 = xmin + pt.x * dx;
                    auto x2 = xmin + ev.button.x * dx;
                    auto y1 = ymin + pt.y * dy;
                    auto y2 = ymin + ev.button.y * dy;
                    xmin = std::min(x1, x2);
                    xmax = std::max(x1, x2);
                    ymin = std::min(y1, y2);
                    ymax = std::max(y1, y2);
                    break;
                } else {
                    zooming = true;
                    pt = {ev.button.x, ev.button.y};
                    old_pt = pt;
                }
            }
            if (zooming) {
                auto cur_pt = win.current_cursor_position();
                if (cur_pt != old_pt) {
                    win.draw_image(0, 0, im);
                    win.draw_line(pt.x, pt.y, cur_pt.x, pt.y,
                                  eighties::color::red);
                    win.draw_line(pt.x, pt.y, pt.x, cur_pt.y,
                                  eighties::color::red);
                    win.draw_line(cur_pt.x, pt.y, cur_pt.x, cur_pt.y,
                                  eighties::color::red);
                    win.draw_line(pt.x, cur_pt.y, cur_pt.x, cur_pt.y,
                                  eighties::color::red);
                    old_pt = cur_pt;
                }
            }
        }
    }
}
