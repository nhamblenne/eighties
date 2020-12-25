/* =======================================================================
 * test1.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/window.hpp"

#include <iostream>
#include <eighties/color.hpp>

int emain(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i) {
        std::cout << "arg " << i << ": " << argv[i] << '\n';
    }
    eighties::window winT(800, 600);
    winT.resize(200, 150);
    winT.resize(640, 480);
    winT.draw_line(0, 0, 639, 479, eighties::color::blue);
    winT.circle(200, 200, 150, eighties::color::red);
    winT.draw_line(200-150, 200-150, 200+150, 200-150, eighties::color::green);
    winT.draw_line(200-150, 200-150, 200-150, 200+150, eighties::color::green);
    winT.draw_line(200+150, 200-150, 200+150, 200+150, eighties::color::green);
    winT.draw_line(200-150, 200+150, 200+150, 200+150, eighties::color::green);
    for (int i = 0; i < 30; ++i) {
        winT.draw_line(0, i, 200, i, eighties::color::blue);
    }
    winT.wait_for_close();
    return 0;
}
