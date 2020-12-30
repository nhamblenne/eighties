/* =======================================================================
 * test-position.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include <eighties/window.hpp>
#include <eighties/image.hpp>
#include <eighties/color.hpp>
#include <eighties/point.hpp>
#include <eighties/event.hpp>
#include <iostream>

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
        auto event = win.get_event(false);
        switch (event.type) {
            case eighties::event_type::none:
                break;
            case eighties::event_type::key_down:
            case eighties::event_type::key_up:
                std::cout << (uint16_t)event.type << " " << std::hex << (uint16_t)event.key.key << " " << (uint16_t)event.key.modifiers << " " << event.key.scan << '\n';
                break;
            case eighties::event_type::button_down:
            case eighties::event_type::button_wheel:
            case eighties::event_type::button_up:
                std::cout << (uint16_t)event.type << " " << std::hex << (uint16_t)event.button.pressed_buttons << " " << (uint16_t)event.button.modifiers << " "
                          << std::dec << event.button.x << ':' << event.button.y << ' ' << std::hex << event.button.modified_button << '\n';
                break;
        }
    }
    return 0;
}
