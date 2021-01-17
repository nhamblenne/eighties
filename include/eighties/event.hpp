#ifndef EIGHTIES_EVENT_HPP
#define EIGHTIES_EVENT_HPP

/* =======================================================================
 * event.hpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include <stdint.h>

namespace eighties {

/// gives the various keys
enum class key_t: uint16_t {
    space             = 0x20,
    exclamation       = 0x21,
    quotation         = 0x22,
    number            = 0x23,
    dollar            = 0x24,
    percent           = 0x25,
    ampersand         = 0x26,
    apostrophe        = 0x27,
    left_parenthesis  = 0x28,
    right_parenthesis = 0x29,
    asterisk          = 0x2a,
    plus              = 0x2b,
    comma             = 0x2c,
    minus             = 0x2d,
    period            = 0x2e,
    slash             = 0x2f,

    digit_0 = 0x30,
    digit_1 = 0x31,
    digit_2 = 0x32,
    digit_3 = 0x33,
    digit_4 = 0x34,
    digit_5 = 0x35,
    digit_6 = 0x36,
    digit_7 = 0x37,
    digit_8 = 0x38,
    digit_9 = 0x39,

    colon     = 0x3a,
    semicolon = 0x3b,
    less      = 0x3c,
    equal     = 0x3d,
    greater   = 0x3e,
    question  = 0x3f,

    at = 0x40,
    a = 0x41,
    b = 0x42,
    c = 0x43,
    d = 0x44,
    e = 0x45,
    f = 0x46,
    g = 0x47,
    h = 0x48,
    i = 0x49,
    j = 0x4a,
    k = 0x4b,
    l = 0x4c,
    m = 0x4d,
    n = 0x4e,
    o = 0x4f,
    p = 0x50,
    q = 0x51,
    r = 0x52,
    s = 0x53,
    t = 0x54,
    u = 0x55,
    v = 0x56,
    w = 0x57,
    x = 0x58,
    y = 0x59,
    z = 0x5a,

    left_bracket  = 0x5b,
    backslash     = 0x5c,
    right_bracket = 0x5d,
    circumflex    = 0x5e,
    underscore    = 0x5f,
    back_quote    = 0x60,
    left_brace    = 0x7b,
    bar           = 0x7c,
    right_brace   = 0x7d,
    tilde         = 0x7e,

    escape    = 0x1000,
    tab       = 0x1001,
    backspace = 0x1002,
    enter     = 0x1003,

    insert    = 0x1005,
    del       = 0x1006,
    home      = 0x1007,
    end       = 0x1008,
    page_up   = 0x1009,
    page_down = 0x100a,

    left  = 0x100b,
    right = 0x100c,
    up    = 0x100d,
    down  = 0x100e,

    f1  = 0x1101,
    f2  = 0x1102,
    f3  = 0x1103,
    f4  = 0x1104,
    f5  = 0x1105,
    f6  = 0x1106,
    f7  = 0x1107,
    f8  = 0x1108,
    f9  = 0x1109,
    f10 = 0x110A,
    f11 = 0x110B,
    f12 = 0x110C,
    f13 = 0x110D,
    f14 = 0x110E,
    f15 = 0x110F,
    f16 = 0x1110,
    f17 = 0x1111,
    f18 = 0x1112,
    f19 = 0x1113,
    f20 = 0x1114,
    f21 = 0x1115,
    f22 = 0x1116,
    f23 = 0x1117,
    f24 = 0x1118,
    f25 = 0x1119,
    f26 = 0x111A,
    f27 = 0x111B,
    f28 = 0x111C,
    f29 = 0x111D,
    f30 = 0x111E,
    f31 = 0x111F,
    f32 = 0x1120,

    unknown = 0xFFFF
};

/// gives the modifiers which can be pressed at the same time as a key or
/// mouse button.
enum class modifiers_t: uint16_t {
    none    = 0x0000,
    shift   = 0x0001,
    control = 0x0002,
    alt     = 0x0004,
    meta    = 0x0008
};

/// combine two modifiers.
inline modifiers_t& operator|=(modifiers_t& left, modifiers_t right)
{
    left = modifiers_t((uint16_t)left | (uint16_t)right);
    return left;
}

/// gives the various event types.
enum class event_type: uint16_t {
    none, ///< no event
    key_down, ///< a key press
    key_up, ///< a key release
    button_down, ///< a mouse button press
    button_wheel, ///< a mouse wheel, note that wheel correspond to buttons 4, 5, 6 and 7
    button_up, ///< a mouse button release
    close ///< window is now closed
};

/// describe a key event
struct key_event {
    modifiers_t modifiers; ///< the modifiers pressed at the same time as the key
    key_t key; ///< the key
    uint16_t scan; ///< the scan code from the system
};

/// describe a button event
struct button_event {
    modifiers_t modifiers; ///< the modifiers pressed at the same time as the button
    uint16_t modified_button; ///< the button whose status change triggered the event
    uint16_t pressed_buttons; ///< all the buttons pressed
    int32_t x; ///< x position of the mouse
    int32_t y; ///< y position of the mouse
};

struct event
{
    event() : type(event_type::none) {}
    event(event_type p_type) : type{p_type} {}
    event(event_type p_type, key_event p_key) : type{p_type}, key{p_key} {}
    event(event_type p_type, button_event p_button) : type{p_type}, button{p_button} {}

    event_type type;
    union {
        key_event key; ///< valid when type is key_down or key_up
        button_event button; ///< valid when type is button_down, button_wheel, button_up
    };
};

}

#endif
