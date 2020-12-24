#ifndef EIGHTIES_WINDOW_HPP
#define EIGHTIES_WINDOW_HPP

/* =======================================================================
 * window.hpp.h
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include <memory>

namespace eighties {

class window_impl;

class window
{
public:
    window(int width, int height);
    window(window&&) noexcept;
    window& operator=(window&&) noexcept;
    ~window();

    void wait_for_close() const;
private:
    std::unique_ptr<window_impl> m_impl;
};

}

#endif
